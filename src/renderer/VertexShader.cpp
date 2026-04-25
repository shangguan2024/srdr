#include "VertexShader.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"
#include <functional>

namespace srdr {

static std::function<VertexOutput(VertexInput)> s_default_vs = [](const VertexInput& in) {
    VertexOutput out;
    const auto& [x, y, z] = in.a_position;
    out.v_position = Vec4(x, y, z, 1.0f);
    out.v_normal = in.a_normal;
    out.v_color = in.a_color;
    out.v_uv = in.a_uv;
    return out;
};

VertexShader::VertexShader()
        : m_vs(s_default_vs) {}

VertexShader::VertexShader(VertexShaderProgram vs)
        : m_vs(vs) {}

void VertexShader::setShader(std::function<VertexOutput(VertexInput)> vs) { m_vs = vs; }

void VertexShader::resetShader() { m_vs = s_default_vs; }

void VertexShader::processVertices(const std::vector<VertexInput>& inputs,
        std::vector<VertexOutput>& outputs) {
    for (const auto& in: inputs) {
        outputs.emplace_back(m_vs(in));
    }
}

} // namespace srdr
