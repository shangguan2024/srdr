#ifndef WIN32_WINDOW_HPP
#define WIN32_WINDOW_HPP

#include "IWindow.hpp"
#include <cstdint>
#include <windows.h>

namespace srdr {

class Win32Window : public IWindow {
public:
    Win32Window() = default;
    ~Win32Window();

    bool create(int width, int height, const char* title) override;
    void destroy() override;

    bool isRunning() override;
    void drawFrame(const uint32_t* pixels) override;

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    HWND m_hWnd = nullptr;
    HDC m_hdcMem = nullptr;
    HBITMAP m_hBitmap = nullptr;
    uint32_t* m_pixels = nullptr;
    int m_width = 0;
    int m_height = 0;
};

} // namespace srdr

#endif // WIN32_WINDOW_HPP
