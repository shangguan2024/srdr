#ifndef FRAGMENT_SHADER_HPP
#define FRAGMENT_SHADER_HPP

#include "Fragment.hpp"
#include <functional>

namespace srdr {

using FragmentShaderProgram = std::function<FragmentOutput(FragmentInput)>;

class FragmentShader {
public:
    FragmentShader();
    FragmentShader(FragmentShaderProgram fs);

    void setShader(FragmentShaderProgram fs);
    void resetShader();

    void processFragments(const std::vector<FragmentInput>& inputs,
            std::vector<FragmentOutput>& outputs);

private:
    FragmentShaderProgram m_fs;
};

} // namespace srdr

#endif // FRAGMENT_SHADER_HPP
