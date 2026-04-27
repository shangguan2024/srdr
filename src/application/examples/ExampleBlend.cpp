#include "ExampleBlend.hpp"
#include "Color.hpp"
#include "Renderer.hpp"
#include "Vertex.hpp"
#include "WindowFactory.hpp"
#include <cstddef>
#include <iostream>
#include <thread>
#include <vector>

namespace srdr {

int ExampleBlend::run() {
    WindowFactory wf;
    auto window = wf.createWindow();
    const int width = 800, height = 600;
    if (!window->create(width, height, "Blend")) {
        std::cerr << "Failed to create window" << std::endl;
        return -1;
    }

    Renderer device(window);

    device.enable(State::BLEND);

    std::vector<Vertex> tris(6);
    std::vector<std::size_t> ind{ 0, 1, 2, 3, 4, 5 };
    tris[0].color = Color(1, 0, 0, 1);
    tris[1].color = Color(1, 0, 0, 1);
    tris[2].color = Color(1, 0, 0, 1);
    tris[0].position = { -0.3, -0.3, 0 };
    tris[1].position = { 0.7, -0.3, 0 };
    tris[2].position = { -0.3, 0.7, 0 };
    tris[3].color = Color(0, 1, 0, 0.0);
    tris[4].color = Color(0, 1, 0, 0.8);
    tris[5].color = Color(0, 1, 0, 0.8);
    tris[3].position = { 0.6, 0.6, 0 };
    tris[4].position = { 0.3, -0.8, 0 };
    tris[5].position = { -0.8, 0.3, 0 };

    while (window->isRunning()) {
        device.clearFrameBuffer();
        device.beginScene();

        device.draw(tris, ind);

        device.endScene();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}

} // namespace srdr
