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

    const auto& v0 = p.vertices[0].position;
    const auto& v1 = p.vertices[1].position;
    const auto& v2 = p.vertices[2].position;

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

    p.edges[0] = edgeFunc(v0.x, v0.y, v1.x, v1.y);
    p.edges[1] = edgeFunc(v1.x, v1.y, v2.x, v2.y);
    p.edges[2] = edgeFunc(v2.x, v2.y, v0.x, v0.y);

    p.depth_plane =
            PlaneEquation::computePlane(v0.x, v0.y, v0.z, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);

    return p;
}

} // namespace srdr
