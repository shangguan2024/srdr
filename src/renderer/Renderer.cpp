#include "Renderer.hpp"
#include "IWindow.hpp"
#include <memory>
#include <utility>

namespace srdr {

Renderer::Renderer(std::shared_ptr<IWindow> window)
        : m_window(std::move(window)) {
    init();
}

void Renderer::init() {
    // TODO
}

} // namespace srdr
