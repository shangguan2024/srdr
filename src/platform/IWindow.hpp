#ifndef IWINDOW_HPP
#define IWINDOW_HPP

#include <cstdint>

namespace srdr {

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual bool create(int width, int height, const char* title) = 0;
    virtual void destroy() = 0;

    virtual bool isRunning() = 0;
    virtual void drawFrame(const uint32_t* pixels) = 0;
};

} // namespace srdr

#endif // IWINDOW_HPP
