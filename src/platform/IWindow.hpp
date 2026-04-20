#ifndef IWINDOW_HPP
#define IWINDOW_HPP

namespace srdr {

class IWindow {
public:
    virtual ~IWindow() = default;
    virtual bool create(int width, int height, const char* title) = 0;
};

} // namespace srdr

#endif // IWINDOW_HPP
