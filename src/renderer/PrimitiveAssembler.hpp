#ifndef PRIMITIVE_ASSEMBLER_HPP
#define PRIMITIVE_ASSEMBLER_HPP

#include "Primitive.hpp"
#include "Vertex.hpp"
#include <vector>

namespace srdr {

class PrimitiveAssembler {
public:
    void assemblePrimitives(const std::vector<VertexOutput>& vertices,
            std::vector<Primitive>& primitives);

private:
    [[nodiscard]] Primitive assemblePrimitive(const VertexOutput& A, const VertexOutput& B,
            const VertexOutput& C);
};

} // namespace srdr

#endif // PRIMITIVE_ASSEMBLER_HPP
