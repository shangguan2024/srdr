#include "PrimitiveAssembler.hpp"
#include "Geometry.hpp"
#include "Primitive.hpp"
#include <cstddef>

namespace srdr {

void PrimitiveAssembler::assemblePrimitives(const std::vector<VertexOutput>& vertices,
        std::vector<Primitive>& primitives) {
    for (std::size_t i = 2ull; i < vertices.size(); i += 3ull) {
        const auto& A = vertices[i - 2ull];
        const auto& B = vertices[i - 1ull];
        const auto& C = vertices[i - 0ull];
        primitives.emplace_back(assemblePrimitive(A, B, C));
    }
}

[[nodiscard]] Primitive PrimitiveAssembler::assemblePrimitive(const VertexOutput& A,
        const VertexOutput& B, const VertexOutput& C) {
    Primitive p;
    p.vertices[0] = A;
    p.vertices[1] = B;
    p.vertices[2] = C;

    const auto& a = A.v_position;
    const auto& b = B.v_position;
    const auto& c = C.v_position;

    // AABB
    p.aabb.min_x = (int) std::min({ a.x, b.x, c.x });
    p.aabb.max_x = (int) std::max({ a.x, b.x, c.x });
    p.aabb.min_y = (int) std::min({ a.y, b.y, c.y });
    p.aabb.max_y = (int) std::max({ a.y, b.y, c.y });

    // signed area
    p.area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

    // ensure counter-clockwise order
    if (p.area < 0) {
        std::swap(p.vertices[1], p.vertices[2]);
        p.area = -p.area;
    }

    const auto& v0 = p.vertices[0].v_position;
    const auto& v1 = p.vertices[1].v_position;
    const auto& v2 = p.vertices[2].v_position;

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
