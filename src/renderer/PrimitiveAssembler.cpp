#include "PrimitiveAssembler.hpp"
#include "Geometry.hpp"
#include "Primitive.hpp"
#include "Vector.hpp"
#include "shader_interfaces/Vertex.hpp"
#include <cstddef>

namespace srdr {

void PrimitiveAssembler::setWindowSize(const Vec2i& window_size) {
    m_width = window_size.x;
    m_height = window_size.y;
}

void PrimitiveAssembler::assemblePrimitives(const std::vector<ClipVertex>& vertices,
        std::vector<Primitive>& primitives) {
    for (std::size_t i = 2ull; i < vertices.size(); i += 3ull) {
        const auto& A = vertices[i - 2ull];
        const auto& B = vertices[i - 1ull];
        const auto& C = vertices[i - 0ull];
        primitives.emplace_back(assemblePrimitive(A, B, C));
    }
}

[[nodiscard]] Primitive PrimitiveAssembler::assemblePrimitive(const ClipVertex& A,
        const ClipVertex& B, const ClipVertex& C) {
    Primitive p;

    auto clipToScreen = [&](const ClipVertex& cv) -> ScreenVertex {
        ScreenVertex sv;
        float& inv_w = sv.inv_w;
        inv_w = 1.0f / cv.v_position.w;

        float ndc_x = cv.v_position.x * inv_w;
        float ndc_y = cv.v_position.y * inv_w;
        float ndc_z = cv.v_position.z * inv_w;

        sv.position.x = (ndc_x * 0.5f + 0.5f) * m_width;
        sv.position.y = (ndc_y * 0.5f + 0.5f) * m_height;
        sv.position.z = ndc_z * 0.5f + 0.5f;

        sv.v_normal = cv.v_normal * inv_w;
        sv.v_color = cv.v_color * inv_w;
        sv.v_uv = cv.v_uv * inv_w;

        return sv;
    };

    p.vertices[0] = clipToScreen(A);
    p.vertices[1] = clipToScreen(B);
    p.vertices[2] = clipToScreen(C);

    const auto& u0 = p.vertices[0].position;
    const auto& u1 = p.vertices[1].position;
    const auto& u2 = p.vertices[2].position;

    // AABB
    p.aabb.min_x = (int) std::min({ u0.x, u1.x, u2.x });
    p.aabb.max_x = (int) std::max({ u0.x, u1.x, u2.x });
    p.aabb.min_y = (int) std::min({ u0.y, u1.y, u2.y });
    p.aabb.max_y = (int) std::max({ u0.y, u1.y, u2.y });

    // signed area
    p.area = (u1.x - u0.x) * (u2.y - u0.y) - (u1.y - u0.y) * (u2.x - u0.x);

    // ensure counter-clockwise order
    if (p.area < 0) {
        std::swap(p.vertices[1], p.vertices[2]);
        p.area = -p.area;
    }

    const auto& v0 = p.vertices[0];
    const auto& v1 = p.vertices[1];
    const auto& v2 = p.vertices[2];

    // edge function: inside > 0 (counter-clockwise)
    // edge Ei from vi to v(i+1)
    auto edgeFunc = [](float x0, float y0, float x1, float y1) -> EdgeEquation {
        // return equation such that point on left side of edge (v0->v1) is positive
        // F(x,y) = (x1 - x0)*(y - y0) - (y1 - y0)*(x - x0)
        float A = y0 - y1;
        float B = x1 - x0;
        float C = x0 * y1 - x1 * y0;
        return EdgeEquation(A, B, C);
    };

    p.edges[0] = edgeFunc(v0.position.x, v0.position.y, v1.position.x, v1.position.y);
    p.edges[1] = edgeFunc(v1.position.x, v1.position.y, v2.position.x, v2.position.y);
    p.edges[2] = edgeFunc(v2.position.x, v2.position.y, v0.position.x, v0.position.y);

    auto planeFunc = [&](float f0, float f1, float f2) -> PlaneEquation {
        return PlaneEquation::computePlane(v0.position.x, v0.position.y, f0, v1.position.x,
                v1.position.y, f1, v2.position.x, v2.position.y, f2);
    };

    p.depth_plane = planeFunc(v0.position.z, v1.position.z, v2.position.z);
    p.inv_w_plane = planeFunc(v0.inv_w, v1.inv_w, v2.inv_w);
    p.rgba_plane[0] = planeFunc(v0.v_color.r, v1.v_color.r, v2.v_color.r);
    p.rgba_plane[1] = planeFunc(v0.v_color.g, v1.v_color.g, v2.v_color.g);
    p.rgba_plane[2] = planeFunc(v0.v_color.b, v1.v_color.b, v2.v_color.b);
    p.rgba_plane[3] = planeFunc(v0.v_color.a, v1.v_color.a, v2.v_color.a);
    p.uv_plane[0] = planeFunc(v0.v_uv[0], v1.v_uv[0], v2.v_uv[0]);
    p.uv_plane[1] = planeFunc(v0.v_uv[1], v1.v_uv[1], v2.v_uv[1]);

    return p;
}

} // namespace srdr
