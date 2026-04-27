#ifndef OUTPUT_MERGER_HPP
#define OUTPUT_MERGER_HPP

#include "Fragment.hpp"
#include "FrameBuffer.hpp"
#include <vector>

namespace srdr {

class OutputMerger {
public:
    void mergeOutputs(const std::vector<FragmentOutput>& outputs, FrameBuffer* fb);

    // TODO
};

} // namespace srdr

#endif // OUTPUT_MERGER_HPP
