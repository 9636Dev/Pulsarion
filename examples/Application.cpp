#include "Pulsarion.h"
#include <memory>

using namespace Pulsarion;

int main(int argc, char** argv) {
    std::unique_ptr<Window> window = CreateWindowPointer(WindowProperties());
    window->SetVSync(false);
    window->SetFrameTimeCount(500);

    while (window->IsOpen())
    {
        window->OnFrame();
        window->SetTitle("Pulsarion - FPS: " + std::to_string(window->GetAverageFps()) + " - " + std::to_string(window->GetAverageFrameTime()) + "ms");
    }

    return 0;
}
