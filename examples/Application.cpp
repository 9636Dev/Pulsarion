#include "Pulsarion.h"
#include <memory>

using namespace Pulsarion;
int main(int argc, char** argv) {
    std::unique_ptr<Window> window = CreateWindowPointer(WindowProperties());

    while (window->IsOpen())
    {
        window->OnFrame();
    }

    return 0;
}
