#include "OutputMerger.hpp"

namespace srdr {

void OutputMerger::mergeOutputs(const std::vector<FragmentOutput>& outputs, FrameBuffer* fb) {
    // TODO: z ...
    for (const auto& pixel: outputs) {
        const auto& [x, y, z] = pixel.o_position;
        fb->writeColor(0, x, y, pixel.o_color);
    }
}

} // namespace srdr
