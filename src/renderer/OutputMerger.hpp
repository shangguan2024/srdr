#ifndef OUTPUT_MERGER_HPP
#define OUTPUT_MERGER_HPP

#include "Fragment.hpp"
#include "FrameBuffer.hpp"
#include <functional>
#include <vector>

namespace srdr {

using BlendFunction = std::function<Color(const Color&, const Color&)>;

class OutputMerger {
public:
    OutputMerger();

    void mergeOutputs(const std::vector<FragmentOutput>& outputs, FrameBuffer* fb);

    void enableDepthTest();
    void disableDepthTest();

    void enableBlend();
    void disableBlend();

    void setBlendFunction(BlendFunction blend_func);
    void resetBlendFunction();

private:
    bool m_enable_depth_test;
    bool m_enable_blend;

    BlendFunction m_blend_function;
};

} // namespace srdr

#endif // OUTPUT_MERGER_HPP
