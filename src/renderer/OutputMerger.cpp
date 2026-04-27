#include "OutputMerger.hpp"
#include "Color.hpp"

namespace srdr {

static BlendFunction s_default_blend_function = [](const Color& src, const Color& dst) {
    Color out;
    out = src * src.a + dst * (1.0f - src.a);
    return out;
};

OutputMerger::OutputMerger()
        : m_blend_function(s_default_blend_function) {}

void OutputMerger::mergeOutputs(const std::vector<FragmentOutput>& outputs, FrameBuffer* fb) {
    for (const auto& pixel: outputs) {
        const auto& [x, y, z] = pixel.o_position;
        auto writeColor = [&]() {
            if (m_enable_blend) {
                fb->writeColor(0, x, y, m_blend_function(pixel.o_color, fb->getColor(0, x, y)));
            } else {
                fb->writeColor(0, x, y, pixel.o_color);
            }
        };
        if (m_enable_depth_test) {
            if (fb->testAndWriteDepth(x, y, z)) {
                writeColor();
            }
        } else {
            writeColor();
        }
    }
}

void OutputMerger::enableDepthTest() { m_enable_depth_test = true; }

void OutputMerger::disableDepthTest() { m_enable_depth_test = false; }

void OutputMerger::enableBlend() { m_enable_blend = true; }

void OutputMerger::disableBlend() { m_enable_blend = false; }

void OutputMerger::setBlendFunction(BlendFunction blend_func) { m_blend_function = blend_func; }

void OutputMerger::resetBlendFunction() { m_blend_function = s_default_blend_function; }

} // namespace srdr
