#include "Win32Window.hpp"
#include <cstdint>
#include <cstring>

namespace srdr {

Win32Window::~Win32Window() { destroy(); }

bool Win32Window::create(int width, int height, const char* title) {
    m_width = width;
    m_height = height;

    // 1. register window class
    WNDCLASSEXA wc = {};
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = "Win32PixelWindow";
    if (!RegisterClassExA(&wc)) return false;

    // 2. calculate window actual size
    RECT rect = { 0, 0, width, height };
    DWORD style = WS_OVERLAPPEDWINDOW;
    AdjustWindowRect(&rect, style, FALSE);
    int winWidth = rect.right - rect.left;
    int winHeight = rect.bottom - rect.top;

    // 3. create window
    m_hWnd = CreateWindowExA(0, wc.lpszClassName, title, style, CW_USEDEFAULT, CW_USEDEFAULT,
            winWidth, winHeight, nullptr, nullptr, wc.hInstance, this);
    if (!m_hWnd) return false;

    // 4. create DIB Section and memory DC
    HDC hdcScreen = GetDC(nullptr);
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    m_hBitmap = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, (void**) &m_pixels, nullptr, 0);
    ReleaseDC(nullptr, hdcScreen);
    if (!m_hBitmap) {
        DestroyWindow(m_hWnd);
        return false;
    }

    m_hdcMem = CreateCompatibleDC(nullptr);
    SelectObject(m_hdcMem, m_hBitmap);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return true;
}

void Win32Window::destroy() {
    if (m_hBitmap) {
        DeleteObject(m_hBitmap);
        m_hBitmap = nullptr;
    }
    if (m_hdcMem) {
        DeleteDC(m_hdcMem);
        m_hdcMem = nullptr;
    }
    if (m_hWnd) {
        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }
    m_pixels = nullptr;
}

bool Win32Window::isRunning() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

void Win32Window::drawFrame(const uint32_t* pixels) {
    if (!m_pixels || !pixels) return;

    // copy pixels to DIB Section buffer
    size_t byteSize = m_width * m_height * sizeof(uint32_t);
    std::memcpy(m_pixels, pixels, byteSize);

    // trigger repaint
    InvalidateRect(m_hWnd, nullptr, FALSE);
    UpdateWindow(m_hWnd);
}

LRESULT CALLBACK Win32Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Win32Window* self = nullptr;

    if (msg == WM_NCCREATE) {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        self = static_cast<Win32Window*>(cs->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    } else {
        self = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (!self) return DefWindowProc(hWnd, msg, wParam, lParam);

    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            if (self->m_hdcMem) {
                BitBlt(hdc, 0, 0, self->m_width, self->m_height, self->m_hdcMem, 0, 0, SRCCOPY);
            }
            EndPaint(hWnd, &ps);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

} // namespace srdr
