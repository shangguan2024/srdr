#include "Rasterizer.hpp"
#include "Color.hpp"
#include "Vector.hpp"
#include <algorithm>

namespace srdr {

void Rasterizer::setWindowSize(const Vec2i& window_size) {
    m_width = window_size.x;
    m_height = window_size.y;
}

void Rasterizer::rasterizePrimitives(const std::vector<Primitive>& primitives,
        std::vector<FragmentInput>& fragments) {
    for (const auto& primitive: primitives) {
        rasterizePrimitive(primitive, fragments);
    }
}

void Rasterizer::rasterizePrimitive(const Primitive& p, std::vector<FragmentInput>& fragments) {
    int min_x = std::max(p.aabb.min_x, 0);
    int max_x = std::min(p.aabb.max_x, m_width - 1);
    int min_y = std::max(p.aabb.min_y, 0);
    int max_y = std::min(p.aabb.max_y, m_height - 1);

    for (int y = min_y; y <= max_y; ++y) {
        float x0 = min_x + 0.5f;
        float y0 = y + 0.5f;
        float e0 = p.edges[0].evaluate(x0, y0);
        float e1 = p.edges[1].evaluate(x0, y0);
        float e2 = p.edges[2].evaluate(x0, y0);
        float d = p.depth_plane.evaluate(x0, y0);
        float inv_w = p.inv_w_plane.evaluate(x0, y0);
        float r = p.rgba_plane[0].evaluate(x0, y0);
        float g = p.rgba_plane[1].evaluate(x0, y0);
        float b = p.rgba_plane[2].evaluate(x0, y0);
        float a = p.rgba_plane[3].evaluate(x0, y0);
        float u = p.uv_plane[0].evaluate(x0, y0);
        float v = p.uv_plane[1].evaluate(x0, y0);

        for (int x = min_x; x <= max_x; ++x) {
            if (e0 >= 0.0f && e1 >= 0.0f && e2 >= 0.0f) {
                // TODO: early-z ...

                auto& fragment = fragments.emplace_back();
                float w = 1.0f / inv_w;
                fragment.f_position = Vec4(x, y, d, w);
                // TODO: fragment.v_normal = ...
                fragment.v_color = Color(r, g, b, a) * w;
                fragment.v_uv = Vec2(u, v) * w;
            }

            e0 += p.edges[0].stepX();
            e1 += p.edges[1].stepX();
            e2 += p.edges[2].stepX();
            d += p.depth_plane.stepX();
            inv_w += p.inv_w_plane.stepX();
            r += p.rgba_plane[0].stepX();
            g += p.rgba_plane[1].stepX();
            b += p.rgba_plane[2].stepX();
            a += p.rgba_plane[3].stepX();
            u += p.uv_plane[0].stepX();
            v += p.uv_plane[1].stepX();
        }
    }
}

} // namespace srdr
