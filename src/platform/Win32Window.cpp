#include "Win32Window.hpp"
#include <cstdint>

namespace srdr {

Win32Window::~Win32Window() {
    // TODO
}

bool Win32Window::create(int width, int height, const char* title) {
    // TODO
    return false;
}

void Win32Window::destroy() {
    // TODO
}

bool Win32Window::isRunning() {
    // TODO
    return false;
}

void Win32Window::drawFrame(const uint32_t* pixels) {
    // TODO
}

LRESULT CALLBACK Win32Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // TODO
    return 0ll;
}

} // namespace srdr
