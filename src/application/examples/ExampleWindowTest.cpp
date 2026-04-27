#include "ExampleWindowTest.hpp"
#include "WindowFactory.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>
#include <vector>

namespace srdr {

int ExampleWindowTest::run() {
    WindowFactory wf;
    auto window = wf.createWindow();
    const int width = 800, height = 600;
    if (!window->create(width, height, "Pixel Display Test")) {
        std::cerr << "Failed to create window" << std::endl;
        return -1;
    }

    std::vector<uint32_t> framebuffer(width * height);

    while (window->isRunning()) {
        static int frame = 0;
        for (int i = 0; i < width * height; ++i) {
            int x = i % width;
            int y = i / width;
            uint8_t r = (x + frame) % 256;
            uint8_t g = (y + frame) % 256;
            uint8_t b = ((x ^ y) + frame) % 256;
            framebuffer[i] = (0xFF << 24) | (r << 16) | (g << 8) | b;
        }
        window->drawFrame(framebuffer.data());
        ++frame;

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}

} // namespace srdr
