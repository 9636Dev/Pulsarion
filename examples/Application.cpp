#include "Pulsarion.h"

#include <memory>
#include <random>

using namespace Pulsarion;

#define PLS_BIND_EVENT_FN(fn) [this]<typename T0>(T0 && PH1) { return fn(std::forward<T0>(PH1)); }
class App
{
public:
    App() : m_Window(CreateWindowPointer(WindowProperties())), m_Renderer(CreateRenderer()),
        m_DisplayScale(std::make_shared<UI::Slider1f>("Display Scale", std::array{ 1.0f }, std::array{ 100.0f }, std::array{ 10.0f })) {
        m_Window->SetEventCallback(PLS_BIND_EVENT_FN(App::OnEvent));
    }

    void OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseScrollEvent>(PLS_BIND_EVENT_FN(App::OnScrollEvent));
    }

    [[nodiscard]] bool OnScrollEvent(const MouseScrollEvent& event) const
    {
        const float newScale = m_DisplayScale->Get(0) - event.GetOffsetY();
        m_DisplayScale->Set(0, newScale);

        return true;
    }

    [[nodiscard]] glm::mat4 GetProjection() const
    {
        const float aspectRatio = static_cast<float>(m_Window->GetWidth()) / static_cast<float>(m_Window->GetHeight());
        return glm::ortho(m_DisplayScale->Get(0) * -aspectRatio, m_DisplayScale->Get(0) * aspectRatio, -m_DisplayScale->Get(0), m_DisplayScale->Get(0));
    }

    void Run()
    {
        using namespace OpenGL;
        m_Renderer->Set2DProjection(GetProjection());

        m_Renderer->SetBlend(true);
        File meshFile("assets/mesh/rectangle_base.plsmesh");
        MeshParseResult parseResult = PLSMesh::Parse(meshFile);
        if (!parseResult.Success)
        {
            std::cout << "Failed to parse mesh from file: " << parseResult.Message << std::endl;
            std::exit(1);
        }

        parseResult.Mesh2D->CreateBackend();
        if (!MeshManager::Add2DMesh("Rectangle", parseResult.Mesh2D))
        {
            std::cout << "Failed to add mesh to manager, probably already exists!" << std::endl;
            std::exit(1);
        }
        std::shared_ptr<Mesh2D> mesh = parseResult.Mesh2D;

        TextureManager::LoadFromTextureList(File("assets/textures/texture_list.json"));
        std::shared_ptr<Material> brick = MaterialManager::CreateMaterial("brick");
        brick->SetTextureId(TextureManager::Get2DTextureID("brick"));
        brick->SetDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        Camera camera;

        auto cameraPosition = std::make_shared<UI::Slider2f>("Camera2D Position", std::array{ -150.0f, -150.0f }, std::array{ 150.0f, 150.0f }, std::array{ 0.0f, 0.0f });
        auto cameraRotation = std::make_shared<UI::Slider1f>("Camera2D Rotation", std::array{ -glm::pi<float>() }, std::array{ glm::pi<float>() }, std::array{ 0.0f });

        std::vector<std::shared_ptr<GraphicalObject2D>> renderables;

        auto text = std::make_shared<UI::Text>("FPS: ");
        m_Window->SetVSync(true);
        auto numRenderables = std::make_shared<UI::Slider1i>("Num Renderables", std::array{ 0 }, std::array{ 1000 }, std::array{ 0 });

        bool vsync = true;
        auto vsyncButton = std::make_shared<UI::Button>("VSync: On");

        bool renderWireframe = false;
        auto wireframe = std::make_shared<UI::Button>("Wireframe: Off");

        UI::Window uiWindow("Controls");
        uiWindow.AddWidget(text);
        uiWindow.AddWidget(numRenderables);
        uiWindow.AddWidget(wireframe);
        uiWindow.AddWidget(vsyncButton);
        uiWindow.AddWidget(m_DisplayScale);
        uiWindow.AddWidget(cameraPosition);
        uiWindow.AddWidget(cameraRotation);

        std::vector<uint64_t> renderableIds;

        // Random distribution between -150 and 150
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-150.0f, 150.0f);

        while (m_Window->IsOpen())
        {
            text->SetText("FPS: " + std::to_string(m_Window->GetAverageFps()) + " (" + std::to_string(m_Window->GetAverageFrameTime()) + "ms / frame).\nRenderables: " + std::to_string(numRenderables->Get(0)) + "\nRender Info : " + Debug::ToString(m_Renderer->GetRenderInfo()));

            if (wireframe->IsPressed())
            {
                renderWireframe = !renderWireframe;
                wireframe->SetText("Wireframe: " + (renderWireframe ? std::string("On") : std::string("Off")));
                m_Renderer->SetWireframeMode(renderWireframe);
            }

            if (vsyncButton->IsPressed())
            {
                vsync = !vsync;
                vsyncButton->SetText("VSync: " + (vsync ? std::string("On") : std::string("Off")));
                m_Window->SetVSync(vsync);
            }

            if (numRenderables->IsUpdated())
            {
                // Resize and generate new renderables
                // If size is larger, reserve space and generate new renderables
                // If size is smaller, remove renderables
                const std::int32_t newSize = numRenderables->Get(0);
                if (newSize > renderables.size())
                {
                    renderables.reserve(newSize);
                    renderableIds.reserve(newSize);
                    for (std::int32_t i = static_cast<std::uint32_t>(renderables.size()); i < newSize; ++i)
                    {
                        auto renderable = std::make_shared<GraphicalObject2D>(brick, mesh);
                        renderable->GetTransformRef().SetTranslation(glm::vec2(dis(gen), dis(gen)));
                        renderable->GetTransformRef().SetRotation(dis(gen));
                        renderables.push_back(renderable);
                        renderableIds.push_back(m_Renderer->Add2DRenderable(renderable));
                    }
                }
                else if (newSize < renderables.size())
                {
                    for (std::int32_t i = newSize; i < renderables.size(); ++i)
                    {
                        m_Renderer->Remove2DRenderable(renderableIds[i]);
                    }
                    renderables.resize(newSize);
                    renderableIds.resize(newSize);
                }
            }

            if (m_DisplayScale->IsUpdated())
                m_Renderer->Set2DProjection(GetProjection());
            if (cameraPosition->IsUpdated())
                camera.Set2DPosition(glm::vec2(cameraPosition->GetValue()[0], cameraPosition->GetValue()[1]));
            if (cameraRotation->IsUpdated())
                camera.Set2DRotation(cameraRotation->GetValue()[0]);

            m_Renderer->Clear();
            m_Renderer->Render(camera);
            m_Renderer->RenderUIWindow(uiWindow);
            m_Window->OnFrame();
        }
    }

private:
    std::shared_ptr<UI::Slider1f> m_DisplayScale;
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Renderer;
};

int main(int argc, char** argv) {
    Initializers::InitLogger();

    App app;
    app.Run();
}
