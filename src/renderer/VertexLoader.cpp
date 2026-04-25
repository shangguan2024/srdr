#include "VertexLoader.hpp"
#include "Vertex.hpp"
#include <cstddef>
#include <ranges>

namespace srdr {

void VertexLoader::loadVertex(const std::vector<Vertex>& vb, const std::vector<std::size_t>& eb,
        std::vector<VertexInput>& cache) {
    for (const auto& [position, normal, color, uv]:
            eb | std::views::transform([&](const size_t& i) { return vb[i]; })) {
        cache.emplace_back(position, normal, color, uv);
    }
}

} // namespace srdr
