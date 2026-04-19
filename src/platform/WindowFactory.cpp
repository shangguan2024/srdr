#include "WindowFactory.hpp"
#include "IWindow.hpp"
#include <memory>

#ifdef SRDR_SYSTEM_WINDOWS
#include "Win32Window.hpp"
#endif

namespace srdr {

WindowFactory::WindowFactory() {}

WindowFactory::~WindowFactory() {}

std::unique_ptr<IWindow> WindowFactory::creatWindow() {
#ifdef SRDR_SYSTEM_WINDOWS
    return std::make_unique<Win32Window>();
#else
    // TODO
#endif
}

} // namespace srdr
