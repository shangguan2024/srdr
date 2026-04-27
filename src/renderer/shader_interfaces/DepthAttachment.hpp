#ifndef DEPTH_ATTACHMENT_HPP
#define DEPTH_ATTACHMENT_HPP

#include <vector>

namespace srdr {

class DepthAttachment {
public:
    DepthAttachment(int width, int height);

    void write(int x, int y, float depth);
    bool test(int x, int y, float depth) const;
    bool testAndWrite(int x, int y, float depth);

    float get(int x, int y) const;

    void clear();

    float* data();
    const float* data() const;

private:
    [[nodiscard]] bool isValidCoord(int x, int y) const noexcept;

    int m_width, m_height;
    std::vector<float> m_depths;
};

} // namespace srdr

#endif // DEPTH_ATTACHMENT_HPP
