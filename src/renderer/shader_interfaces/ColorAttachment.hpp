#ifndef COLOR_ATTACHMENT_HPP
#define COLOR_ATTACHMENT_HPP

#include <cstdint>
#include <vector>

namespace srdr {

class ColorAttachment {
public:
    ColorAttachment(int width, int height);

    void write(int x, int y, std::uint32_t color);

    std::uint32_t get(int x, int y) const;

    void clear();

    std::uint32_t* data();
    const std::uint32_t* data() const;

private:
    [[nodiscard]] bool isValidCoord(int x, int y) const noexcept;

    int m_width, m_height;
    std::vector<std::uint32_t> m_colors;
};

} // namespace srdr

#endif // COLOR_ATTACHMENT_HPP
