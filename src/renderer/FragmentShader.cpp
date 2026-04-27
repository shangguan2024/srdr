#include "FragmentShader.hpp"
#include "Fragment.hpp"
#include "Vector.hpp"

namespace srdr {

static FragmentShaderProgram s_default_fs = [](const FragmentInput& in) {
    FragmentOutput out;
    const auto& [x, y, z, w] = in.f_position;
    out.o_position = Vec3(x, y, z);
    out.o_color = in.v_color;
    return out;
};

FragmentShader::FragmentShader()
        : m_fs(s_default_fs) {}

FragmentShader::FragmentShader(FragmentShaderProgram fs)
        : m_fs(fs) {}

void FragmentShader::setShader(FragmentShaderProgram fs) { m_fs = fs; }

void FragmentShader::resetShader() { m_fs = s_default_fs; }

void FragmentShader::processFragments(const std::vector<FragmentInput>& inputs,
        std::vector<FragmentOutput>& outputs) {
    for (const auto& in: inputs) {
        outputs.emplace_back(m_fs(in));
    }
}

} // namespace srdr
