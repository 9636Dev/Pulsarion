#include "Pulsarion.h"
#include <memory>

using namespace Pulsarion;
int main(int argc, char** argv) {
    std::unique_ptr<Window> window = CreateWindowPointer(WindowProperties());

    while (window->IsOpen())
    {
        window->OnFrame();
        float fps = window->GetAverageFps();
        window->SetTitle("Pulsarion - FPS: " + std::to_string(fps));
    }

    return 0;
}
