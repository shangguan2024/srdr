#ifndef WINDOWFACTORY_HPP
#define WINDOWFACTORY_HPP

#include "IWindow.hpp"
#include <memory>

namespace srdr {

class WindowFactory {
public:
    WindowFactory() = default;
    ~WindowFactory() = default;

    std::unique_ptr<IWindow> creatWindow();

private:
};

} // namespace srdr

#endif // WINDOWFACTORY_HPP
