#include "Pulsarionpch.h"
#include "Core/Window.h"

#include "Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"

#include "Test.h"

#include "Core/Backend/OpenGL/VertexArray.h"

#include "UI/Window.h"
#include "UI/Text.h"
#include "UI/ColorPicker.h"
#include "UI/Button.h"
#include "UI/Slider.h"

#include "Core/Renderer.h"
#include "Core/Transform.h"
#include "Core/Backend/MeshBackend.h"
#include "Core/Mesh.h"
#include "Core/MeshManager.h"
#include "Core/Material.h"
#include "Core/MaterialManager.h"
#include "Core/Texture.h"
#include "Core/TextureManager.h"
#include "Core/Shader.h"
#include "Core/ShaderManager.h"
#include "Core/Camera.h"
#include "Core/GraphicalObject.h"

#include "Core/Format/PLSMesh.h"

#include "GL/glew.h"

namespace Pulsarion
{

#define PLS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
    class App
    {
    public:
        App() : m_Window(CreateWindowPointer(WindowProperties())), m_Renderer(CreateRenderer()), m_ViewScale(10.0f) {
            m_Window->SetEventCallback(PLS_BIND_EVENT_FN(App::OnEvent));
        }

        void OnEvent(Event& event)
        {
            PLS_LOG_TRACE("{0}", event.ToString());
            EventDispatcher dispatcher(event);
            dispatcher.Dispatch<MouseScrollEvent>(PLS_BIND_EVENT_FN(App::OnScrollEvent));
        }

        bool OnScrollEvent(const MouseScrollEvent& event)
        {
            PLS_LOG_TRACE("{0}", event.ToString());
            // Increase or decrease view scale based on scroll
            m_ViewScale += event.GetOffsetY();
            m_Renderer->Set2DProjection(GetProjection());
            return true;
        }

        glm::mat4 GetProjection()
        {
            float aspectRatio = static_cast<float>(m_Window->GetWidth()) / static_cast<float>(m_Window->GetHeight());
            return glm::ortho(m_ViewScale * -aspectRatio, m_ViewScale * aspectRatio, -m_ViewScale, m_ViewScale);
        }

        void Run()
        {
            using namespace OpenGL;
            m_Renderer->Set2DProjection(GetProjection());

            m_Renderer->SetBlend(true);
            std::vector<float> vertexPositions = {
                    -0.5f,  0.5f,
                    0.5f,  0.5f,
                    -0.5f, -0.5f,
                    0.5f, -0.5f,
            };
            std::vector<float> textureCoords = {
                    -1.0f,  1.0f,
                    1.0f,  1.0f,
                    -1.0f, -1.0f,
                    1.0f, -1.0f
            };
            std::vector<std::uint32_t> indices = { 0, 1, 2, 1, 2, 3 };

            File meshFile("assets/mesh/rectangle.plsmesh");
            MeshParseResult parseResult = PLSMesh::Parse(meshFile);
            if (!parseResult.Success)
            {
                PLS_LOG_ERROR("Failed to parse mesh from file: {0}", parseResult.Message);
                std::exit(1);
            }

            parseResult.Mesh2D->CreateBackend();
            std::uint32_t meshId = MeshManager::Add2DMesh(parseResult.Mesh2D);
            auto mesh = parseResult.Mesh2D;

            Image brickImage(File("assets/textures/brick.png"));
            std::shared_ptr<Material> brick = MaterialManager::CreateMaterial("brick");
            brick->SetTextureId(TextureManager::CreateTexture2D("brick", brickImage));
            brick->SetDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

            std::shared_ptr<GraphicalObject2D> object = std::make_shared<GraphicalObject2D>(brick, mesh);
            Camera camera;

            std::shared_ptr<UI::Slider1f> displayScale = std::make_shared<UI::Slider1f>("Display Scale", std::array{ 1.0f }, std::array{ 100.0f }, std::array{ 10.0f });
            std::shared_ptr<UI::Slider2f> cameraPosition = std::make_shared<UI::Slider2f>("Camera2D Position", std::array{ -1500.0f, -1.5f }, std::array{ 1500.0f, 1500.0f }, std::array{ 0.0f, 0.0f });
            std::shared_ptr<UI::Slider1f> cameraRotation = std::make_shared<UI::Slider1f>("Camera2D Rotation", std::array{ -glm::pi<float>() }, std::array{ glm::pi<float>() }, std::array{ 0.0f });

            std::shared_ptr<UI::Slider2f> translation = std::make_shared<UI::Slider2f>("Translation", std::array{ -1000.0f, -1000.0f }, std::array{ 1000.0f, 1000.0f }, std::array{ 0.0f, 0.0f });
            std::shared_ptr<UI::Slider2f> scale = std::make_shared<UI::Slider2f>("Scale", std::array{ 0.0f, 0.0f }, std::array{ 100.0f, 100.0f }, std::array{ 10.0f, 10.0f });
            std::shared_ptr<UI::Slider1f> rotation = std::make_shared<UI::Slider1f>("Rotation", std::array{ -glm::pi<float>() }, std::array{ glm::pi<float>() }, std::array{ 0.0f });

            std::shared_ptr<UI::Text> text = std::make_shared<UI::Text>("FPS: ");
            std::shared_ptr<UI::ColorPicker4> clearColor = std::make_shared<UI::ColorPicker4>("Clear Color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            std::shared_ptr<UI::ColorPicker4> fragmentColor = std::make_shared<UI::ColorPicker4>("Fragment Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            m_Renderer->SetClearColor(clearColor->GetColor());
            m_Window->SetVSync(true);

            bool vsync = true;
            std::shared_ptr<UI::Button> vsyncButton = std::make_shared<UI::Button>("VSync: On");

            bool renderWireframe = false;
            std::shared_ptr<UI::Button> wireframe = std::make_shared<UI::Button>("Wireframe: Off");
            UI::Window uiWindow("Controls");
            uiWindow.AddWidget(text);
            uiWindow.AddWidget(clearColor);
            uiWindow.AddWidget(fragmentColor);
            uiWindow.AddWidget(wireframe);
            uiWindow.AddWidget(vsyncButton);
            uiWindow.AddWidget(displayScale);
            uiWindow.AddWidget(cameraPosition);
            uiWindow.AddWidget(cameraRotation);
            uiWindow.AddWidget(translation);
            uiWindow.AddWidget(scale);
            uiWindow.AddWidget(rotation);

            m_Renderer->Add2DRenderable(object);

            // Sync the object's transform with the UI
            object->GetTransformRef().SetTranslation(glm::vec2(translation->GetValue()[0], translation->GetValue()[1]));
            object->GetTransformRef().SetScale(glm::vec2(scale->GetValue()[0], scale->GetValue()[1]));
            object->GetTransformRef().SetRotation(rotation->GetValue()[0]);

            while (m_Window->IsOpen())
            {
                text->SetText("FPS: " + std::to_string(m_Window->GetAverageFps()) + " (" + std::to_string(m_Window->GetAverageFrameTime()) + "ms / frame)");

                if (clearColor->IsUpdated())
                    m_Renderer->SetClearColor(clearColor->GetColor());

                if (fragmentColor->IsUpdated())
                {
                    brick->SetDiffuseColor(fragmentColor->GetColor());
                }

                if (wireframe->IsPressed())
                {
                    renderWireframe = !renderWireframe;
                    if (renderWireframe)
                    {
                        wireframe->SetText("Wireframe: On");
                        m_Renderer->SetWireframeMode(true);
                    }
                    else
                    {
                        wireframe->SetText("Wireframe: Off");
                        m_Renderer->SetWireframeMode(false);
                    }
                }

                if (vsyncButton->IsPressed())
                {
                    vsync = !vsync;
                    if (vsync)
                    {
                        vsyncButton->SetText("VSync: On");
                        m_Window->SetVSync(true);
                    }
                    else
                    {
                        vsyncButton->SetText("VSync: Off");
                        m_Window->SetVSync(false);
                    }
                }

                if (displayScale->IsUpdated())
                {
                    m_ViewScale = displayScale->GetValue()[0];
                    m_Renderer->Set2DProjection(GetProjection());
                }

                if (cameraPosition->IsUpdated())
                    camera.Set2DPosition(glm::vec2(cameraPosition->GetValue()[0], cameraPosition->GetValue()[1]));

                if (cameraRotation->IsUpdated())
                    camera.Set2DRotation(cameraRotation->GetValue()[0]);

                if (translation->IsUpdated())
                    object->GetTransformRef().SetTranslation(glm::vec2(translation->GetValue()[0], translation->GetValue()[1]));

                if (scale->IsUpdated())
                    object->GetTransformRef().SetScale(glm::vec2(scale->GetValue()[0], scale->GetValue()[1]));

                if (rotation->IsUpdated())
                    object->GetTransformRef().SetRotation(rotation->GetValue()[0]);

                m_Renderer->Clear();
                if (brick->GetTextureId().has_value())
                    TextureManager::Bind2DTexture(brick->GetTextureId().value(), 1);
                m_Renderer->Render(camera);

                m_Renderer->RenderUIWindow(uiWindow);

                m_Window->OnFrame();
            }
        }

    private:
        float m_ViewScale;
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Renderer> m_Renderer;
    };

    void Test() {
        App app;
        app.Run();
    }

}
