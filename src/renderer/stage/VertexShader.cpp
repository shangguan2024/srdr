#include "VertexShader.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"
#include <functional>

namespace srdr {

static VertexShaderProgram s_default_vs = [](const VertexInput& in) {
    VertexOutput out;
    out.v_position = Vec4(in.a_position, 1.0f);
    out.v_normal = in.a_normal;
    out.v_color = in.a_color;
    out.v_uv = in.a_uv;
    return out;
};

VertexShader::VertexShader()
        : m_vs(s_default_vs) {}

VertexShader::VertexShader(VertexShaderProgram vs)
        : m_vs(std::move(vs)) {}

void VertexShader::setShader(VertexShaderProgram vs) { m_vs = std::move(vs); }

void VertexShader::resetShader() { m_vs = s_default_vs; }

void VertexShader::processVertices(const std::vector<VertexInput>& inputs,
        std::vector<VertexOutput>& outputs) {
    for (const auto& in: inputs) {
        outputs.emplace_back(m_vs(in));
    }
}

} // namespace srdr
