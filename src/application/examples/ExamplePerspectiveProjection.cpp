#include "ExamplePerspectiveProjection.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Matrix.hpp"
#include "Renderer.hpp"
#include "Transform.hpp"
#include "Vertex.hpp"
#include "WindowFactory.hpp"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <thread>
#include <vector>

namespace srdr {

int ExamplePerspectiveProjection::run() {
    WindowFactory wf;
    auto window = wf.createWindow();
    const int width = 800, height = 600;
    if (!window->create(width, height, "Perspective Projection")) {
        std::cerr << "Failed to create window" << std::endl;
        return -1;
    }

    Renderer device(window);
    device.enable(State::DEPTH_TEST);

    Camera camera(Vec3(0, 0, 3), Vec3(0, 0, 0), Vec3(0, 1, 0), 1.0472f,
            float(width) / float(height), 0.1f, 100.0f);

    float angle = 0.0f;

    device.setVertexShader([&camera, &angle](const VertexInput& in) {
        Mat4 model = transform::rotate(angle, { 0.0f, 1.0f, 0.0f });
        Mat4 mvp = camera.getProjectionMatrix() * camera.getViewMatrix() * model;
        Vec4 clip = mvp * Vec4(in.a_position, 1.0f);
        VertexOutput out;
        out.v_position = clip;
        out.v_color = in.a_color;
        return out;
    });

    std::vector<Vertex> verts = {
        { { -0.5f, -0.5f, -0.5f }, {}, Color(1, 0, 0), {} },
        { { 0.5f, -0.5f, -0.5f }, {}, Color(0, 1, 0), {} },
        { { 0.5f, 0.5f, -0.5f }, {}, Color(0, 0, 1), {} },
        { { -0.5f, 0.5f, -0.5f }, {}, Color(1, 1, 0), {} },
        { { -0.5f, -0.5f, 0.5f }, {}, Color(1, 0, 1), {} },
        { { 0.5f, -0.5f, 0.5f }, {}, Color(0, 1, 1), {} },
        { { 0.5f, 0.5f, 0.5f }, {}, Color(1, 1, 1), {} },
        { { -0.5f, 0.5f, 0.5f }, {}, Color(0.5f, 0, 0.5f), {} },
    };

    std::vector<std::size_t> idx = {
        4,
        5,
        6,
        4,
        6,
        7,
        1,
        0,
        3,
        1,
        3,
        2,
        7,
        6,
        2,
        7,
        2,
        3,
        0,
        1,
        5,
        0,
        5,
        4,
        5,
        1,
        2,
        5,
        2,
        6,
        0,
        4,
        7,
        0,
        7,
        3,
    };

    while (window->isRunning()) {
        device.clearFrameBuffer();
        device.beginScene();

        device.draw(verts, idx);

        device.endScene();

        angle += 0.025f;

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}

} // namespace srdr
