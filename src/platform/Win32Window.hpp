#ifndef WIN32WINDOW_HPP
#define WIN32WINDOW_HPP

#include "IWindow.hpp"

namespace srdr {

class Win32Window : public IWindow {
public:
    Win32Window();
    ~Win32Window();

    bool create(int width, int height, const char* title) override;

private:
};

} // namespace srdr

#endif // WIN32WINDOW_HPP
