#ifndef WINDOW_FACTORY_HPP
#define WINDOW_FACTORY_HPP

#include "IWindow.hpp"
#include <memory>

namespace srdr {

class WindowFactory {
public:
    WindowFactory() = default;
    ~WindowFactory() = default;

    std::unique_ptr<IWindow> createWindow();
};

} // namespace srdr

#endif // WINDOW_FACTORY_HPP
