// test

#include "Win32Window.hpp"
#include <cstdint>
#include <vector>

using namespace srdr;

int main() {
    Win32Window window;
    if (!window.create(800, 600, "Pixel Display Test")) return -1;

    std::vector<uint32_t> framebuffer(800 * 600);

    while (window.isRunning()) {
        static int frame = 0;
        for (int i = 0; i < 800 * 600; ++i) {
            int x = i % 800;
            int y = i / 800;
            uint8_t r = (x + frame) % 256;
            uint8_t g = (y + frame) % 256;
            uint8_t b = ((x ^ y) + frame) % 256;
            framebuffer[i] = (0xFF << 24) | (r << 16) | (g << 8) | b;
        }
        window.drawFrame(framebuffer.data());
        ++frame;

        Sleep(16);
    }

    return 0;
}
