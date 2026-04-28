#ifndef VERTEX_LOADER_HPP
#define VERTEX_LOADER_HPP

#include "Vertex.hpp"
#include <cstddef>
#include <vector>

namespace srdr {

class VertexLoader {
public:
    void loadVertex(const std::vector<Vertex>& vb, const std::vector<std::size_t>& eb,
            std::vector<VertexInput>& cache);
};

} // namespace srdr

#endif // VERTEX_LOADER_HPP
