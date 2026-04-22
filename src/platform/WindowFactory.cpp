#include "WindowFactory.hpp"
#include "IWindow.hpp"
#include <memory>

#ifdef SRDR_SYSTEM_WINDOWS
#include "Win32Window.hpp"
#endif

namespace srdr {

std::shared_ptr<IWindow> WindowFactory::createWindow() {
#ifdef SRDR_SYSTEM_WINDOWS
    return std::make_shared<Win32Window>();
#else
    // TODO
#endif
}

} // namespace srdr
