#ifndef VERTEX_SHADER_HPP
#define VERTEX_SHADER_HPP

#include "Vertex.hpp"
#include <functional>

namespace srdr {

using VertexShaderProgram = std::function<VertexOutput(VertexInput)>;

class VertexShader {
public:
    VertexShader();
    VertexShader(VertexShaderProgram vs);

    void setShader(VertexShaderProgram vs);
    void resetShader();

    void processVertices(const std::vector<VertexInput>& inputs,
            std::vector<VertexOutput>& outputs);

private:
    VertexShaderProgram m_vs;
};

} // namespace srdr

#endif // VERTEX_SHADER_HPP
