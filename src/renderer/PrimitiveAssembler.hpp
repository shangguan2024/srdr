#ifndef PRIMITIVE_ASSEMBLER_HPP
#define PRIMITIVE_ASSEMBLER_HPP

#include "Primitive.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"
#include <vector>

namespace srdr {

class PrimitiveAssembler {
public:
    void setWindowSize(const Vec2i& window_size);

    void assemblePrimitives(const std::vector<ClipVertex>& vertices,
            std::vector<Primitive>& primitives);

private:
    [[nodiscard]] Primitive assemblePrimitive(const ClipVertex& A, const ClipVertex& B,
            const ClipVertex& C);

    int m_width, m_height; // window size
};

} // namespace srdr

#endif // PRIMITIVE_ASSEMBLER_HPP
