#ifndef EXAMPLE_PHONG_LIGHTING_HPP
#define EXAMPLE_PHONG_LIGHTING_HPP

#include "Vertex.hpp"
#include <vector>

namespace srdr {

class ExamplePhongLighting {
public:
    int run();

private:
    void getCube(std::vector<Vertex>& verts, std::vector<std::size_t>& idx);
};

} // namespace srdr

#endif // EXAMPLE_PHONG_LIGHTING_HPP
