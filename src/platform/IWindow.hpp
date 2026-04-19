#ifndef IWINDOW_HPP
#define IWINDOW_HPP

#include "Color.hpp"

namespace srdr {

class IWindow {
public:
    virtual ~IWindow() = default;
    virtual bool create(int width, int height, const char* title) = 0;

    virtual void putPixel(int x, int y, const Color& color) = 0;
};

} // namespace srdr

#endif // IWINDOW_HPP
