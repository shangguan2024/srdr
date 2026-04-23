#ifndef DEPTH_BUFFER_HPP
#define DEPTH_BUFFER_HPP

#include <vector>

namespace srdr {

class DepthBuffer {
public:
    explicit DepthBuffer(int width, int height);

    void update(int x, int y, float depth);
    bool test(int x, int y, float z) const;
    bool testAndUpdate(int x, int y, float z);

    float* data();
    const float* data() const;

private:
    [[nodiscard]] bool isValidCoord(int x, int y) const noexcept;

    int m_width, m_height;
    std::vector<float> m_depths;
};

} // namespace srdr

#endif // DEPTH_BUFFER_HPP
