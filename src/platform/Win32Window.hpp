#ifndef WIN32WINDOW_HPP
#define WIN32WINDOW_HPP

#include "Color.hpp"
#include "IWindow.hpp"

namespace srdr {

class Win32Window : public IWindow {
public:
    Win32Window();
    ~Win32Window();

    bool create(int width, int height, const char* title) override;

    void putPixel(int x, int y, const Color& color) override;

private:
};

} // namespace srdr

#endif // WIN32WINDOW_HPP
