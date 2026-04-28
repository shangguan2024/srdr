#include "ExampleBlend.hpp"
#include "ExampleDepthTest.hpp"
#include "ExampleDrawTriangle.hpp"
#include "ExamplePerspectiveProjection.hpp"
#include "ExamplePhongLighting.hpp"
#include "ExampleWindowTest.hpp"
#include <iostream>
#include <iterator>

void run(int choice) {
    switch (choice) {
        case 1:
            srdr::ExampleWindowTest().run();
            break;
        case 2:
            srdr::ExampleDrawTriangle().run();
            break;
        case 3:
            srdr::ExampleDepthTest().run();
            break;
        case 4:
            srdr::ExampleBlend().run();
            break;
        case 5:
            srdr::ExamplePerspectiveProjection().run();
            break;
        case 6:
            srdr::ExamplePhongLighting().run();
            break;
    }
}

int main() {
    std::string examples[] = {
        "Window Test",
        "Draw Triangle",
        "Depth Test",
        "Blend",
        "Perspective Projection",
        "Phong Lighting",
    };
    std::cout << "\nSRDR Examples\n";
    for (std::size_t i = 0; i < std::size(examples); ++i) {
        std::cout << "  " << (i + 1) << ". " << examples[i] << "\n";
    }
    std::cout << "  x. Exit\n";

    int choice = -1;
    std::cout << "Select: ";
    std::cin >> choice;

    if (1 <= choice && choice <= std::size(examples)) {
        run(choice);
    }

    return 0;
}
