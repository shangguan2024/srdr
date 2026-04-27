#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

#include "Fragment.hpp"
#include "Primitive.hpp"
#include <vector>

namespace srdr {

class Rasterizer {
public:
    void setWindowSize(const Vec2i& window_size);

    void rasterizePrimitives(const std::vector<Primitive>& primitives,
            std::vector<FragmentInput>& fragments);

private:
    void rasterizePrimitive(const Primitive& primitive, std::vector<FragmentInput>& fragments);

    int m_width, m_height; // window size
};

} // namespace srdr

#endif // RASTERIZER_HPP
