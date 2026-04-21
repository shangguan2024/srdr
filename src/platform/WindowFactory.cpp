#include "WindowFactory.hpp"
#include "IWindow.hpp"
#include <memory>

#ifdef SRDR_SYSTEM_WINDOWS
#include "Win32Window.hpp"
#endif

namespace srdr {

std::unique_ptr<IWindow> WindowFactory::createWindow() {
#ifdef SRDR_SYSTEM_WINDOWS
    return std::make_unique<Win32Window>();
#else
    // TODO
#endif
}

} // namespace srdr
