#include "ExamplePhongLighting.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Fragment.hpp"
#include "Light.hpp"
#include "Matrix.hpp"
#include "Renderer.hpp"
#include "Transform.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"
#include "WindowFactory.hpp"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <thread>
#include <vector>

namespace srdr {

int ExamplePhongLighting::run() {
    WindowFactory wf;
    auto window = wf.createWindow();
    const int width = 800, height = 600;
    if (!window->create(width, height, "Phong Lighting")) {
        std::cerr << "Failed to create window" << std::endl;
        return -1;
    }

    Renderer device(window);
    device.enable(State::DEPTH_TEST);

    Camera camera(Vec3(0, -1, 2), Vec3(0, 0, 0), Vec3(0, 1, 0), 1.0472f,
            float(width) / float(height), 0.1f, 100.0f);

    float angle = 0.0f;

    device.setVertexShader([&camera, &angle](const VertexInput& in) {
        Mat4 model = transform::rotate(angle, { 0.0f, 1.0f, 0.0f });
        Mat4 mvp = camera.getProjectionMatrix() * camera.getViewMatrix() * model;
        Vec4 clip = mvp * Vec4(in.a_position, 1.0f);
        VertexOutput out;
        out.v_position = clip;
        out.v_normal = Vec3(model * Vec4(in.a_normal, 0.0f));
        out.v_color = in.a_color;
        out.v_world_position = model * Vec4(in.a_position, 1.0f);
        return out;
    });

    DirectionalLight dl{ normalize(Vec3(-0.5f, -0.8f, 1.0f)), Color(1.0f, 0.95f, 0.9f), 0.8f };
    PointLight pl{ Vec3(0.7f, -0.7f, 0.3f), Color(0.3f, 0.0f, 0.6f), 0.8f, 1.0f, 0.09f, 0.032f };

    Vec3 camera_pos(0, -1, 2);

    device.setFragmentShader([&dl, &pl, &camera_pos](const FragmentInput& in) {
        FragmentOutput out;
        out.o_position = in.f_position;

        Vec3 N = normalize(in.v_normal);
        Vec3 V = normalize(camera_pos - Vec3(in.v_world_position));

        float shininess = 32.0f;
        float ks = 0.5f;

        Vec3 rgb(0.08f, 0.08f, 0.08f);

        Vec3 L = normalize(dl.direction);
        Vec3 H = normalize(L + V);
        float diff_d = std::max(dot(N, L), 0.0f);
        float spec_d = std::pow(std::max(dot(N, H), 0.0f), shininess);
        rgb += dl.color.rgb() * dl.intensity * (diff_d + ks * spec_d);

        Vec3 Lp = normalize(pl.position - Vec3(in.v_world_position));
        Vec3 Hp = normalize(Lp + V);
        float dist = length(pl.position - Vec3(in.v_world_position));
        float att = 1.0f / (pl.constant + pl.linear * dist + pl.quadratic * dist * dist);
        float diff_p = std::max(dot(N, Lp), 0.0f);
        float spec_p = std::pow(std::max(dot(N, Hp), 0.0f), shininess);
        rgb += pl.color.rgb() * pl.intensity * (diff_p + ks * spec_p) * att;

        out.o_color = Color(rgb * in.v_color.rgb(), in.v_color.a);
        return out;
    });

    std::vector<Vertex> verts;
    std::vector<std::size_t> idx;
    getCube(verts, idx);

    while (window->isRunning()) {
        auto start = std::chrono::high_resolution_clock::now();

        device.clearFrameBuffer();
        device.beginScene();

        device.draw(verts, idx);

        device.endScene();

        angle += 0.025f;

        auto end = std::chrono::high_resolution_clock::now();
        int duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(16 - duration));
    }

    return 0;
}

void ExamplePhongLighting::getCube(std::vector<Vertex>& verts, std::vector<std::size_t>& idx) {
    std::vector<Vec3> v{
        { -0.5f, -0.5f, -0.5f }, // 0 0 0
        { -0.5f, -0.5f, 0.5f },  // 0 0 1
        { -0.5f, 0.5f, -0.5f },  // 0 1 0
        { -0.5f, 0.5f, 0.5f },   // 0 1 1
        { 0.5f, -0.5f, -0.5f },  // 1 0 0
        { 0.5f, -0.5f, 0.5f },   // 1 0 1
        { 0.5f, 0.5f, -0.5f },   // 1 1 0
        { 0.5f, 0.5f, 0.5f },    // 1 1 1
    };

    auto add = [&](int a, int b, int c, int d) {
        std::size_t base = verts.size();
        Vec3 normal = normalize(cross(v[b] - v[a], v[d] - v[a]));
        Color color(1, 1, 1, 1);
        verts.push_back({ v[a], normal, color, {} });
        verts.push_back({ v[b], normal, color, {} });
        verts.push_back({ v[c], normal, color, {} });
        verts.push_back({ v[d], normal, color, {} });
        idx.emplace_back(base + 0);
        idx.emplace_back(base + 1);
        idx.emplace_back(base + 2);
        idx.emplace_back(base + 2);
        idx.emplace_back(base + 3);
        idx.emplace_back(base + 0);
    };

    add(0b000, 0b100, 0b101, 0b001);
    add(0b000, 0b010, 0b110, 0b100);
    add(0b000, 0b001, 0b011, 0b010);
    add(0b111, 0b101, 0b100, 0b110);
    add(0b111, 0b011, 0b001, 0b101);
    add(0b111, 0b110, 0b010, 0b011);
}

} // namespace srdr
