#include "ExampleDrawTriangle.hpp"
#include "Color.hpp"
#include "Renderer.hpp"
#include "Vertex.hpp"
#include "WindowFactory.hpp"
#include <cstddef>
#include <iostream>
#include <thread>
#include <vector>

namespace srdr {

int ExampleDrawTriangle::run() {
    WindowFactory wf;
    auto window = wf.createWindow();
    const int width = 800, height = 600;
    if (!window->create(width, height, "Test")) {
        std::cerr << "Failed to create window" << std::endl;
        return -1;
    }

    Renderer device(window);

    std::vector<Vertex> tri(3);
    std::vector<std::size_t> ind{ 0, 1, 2 };
    tri[0].color = Color(1, 0, 0);
    tri[1].color = Color(0, 1, 0);
    tri[2].color = Color(0, 0, 1);
    tri[0].position = { 0, 0, 0 };
    tri[1].position = { 1, 1, 0 };
    tri[2].position = { 0, 1, 0 };

    while (window->isRunning()) {
        device.beginScene();

        device.draw(tri, ind);

        device.endScene();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}

} // namespace srdr
