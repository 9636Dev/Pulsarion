#include "Pulsarionpch.h"
#include "Core/Window.h"

#include "Test.h"

#include "Core/Backend/OpenGL/VertexArray.h"
#include "Core/Backend/OpenGL/VertexBuffer.h"
#include "Core/Backend/OpenGL/IndexBuffer.h"
#include "Core/Backend/OpenGL/Shader.h"
#include "Core/Backend/OpenGL/Texture.h"

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

#include "GL/glew.h"

namespace Pulsarion
{
    void Test()
    {
        using namespace OpenGL;
        std::unique_ptr<Window> window = CreateWindowPointer(WindowProperties());
        window->SetEventCallback([](Event& event) { });
        std::unique_ptr<Renderer> renderer = CreateRenderer();
        renderer->SetBlend(true);
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

  
        auto [meshId, mesh] = MeshManager::Create2DMesh(UsageType::Static, VertexDataType::Interleaved);
        mesh->GetVertexDataRef().SetVertexCount(4);
        mesh->GetVertexDataRef().SetVertices(vertexPositions);
        mesh->GetVertexDataRef().SetTextureCoordinates(textureCoords);
        mesh->SetIndices(indices);
        mesh->CreateBackend();

        Image brickImage(File("assets/textures/brick.png"));
        std::shared_ptr<Material> brick = MaterialManager::CreateMaterial("brick");
        brick->SetTextureId(TextureManager::CreateTexture2D("brick", brickImage));
        brick->SetDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        std::shared_ptr<GraphicalObject2D> object = std::make_shared<GraphicalObject2D>(brick, mesh);
        Camera camera;

        std::shared_ptr<UI::Slider2f> cameraPosition = std::make_shared<UI::Slider2f>("Camera2D Position", std::array{ -1.5f, -1.5f }, std::array{ 1.5f, 1.5f }, std::array{ 0.0f, 0.0f });
        std::shared_ptr<UI::Slider1f> cameraRotation = std::make_shared<UI::Slider1f>("Camera2D Rotation", std::array{ -glm::pi<float>() }, std::array{ glm::pi<float>() }, std::array{ 0.0f });

        std::shared_ptr<UI::Slider2f> translation = std::make_shared<UI::Slider2f>("Translation", std::array{ -1.0f, -1.0f }, std::array{ 1.0f, 1.0f }, std::array{ 0.0f, 0.0f });
        std::shared_ptr<UI::Slider2f> scale = std::make_shared<UI::Slider2f>("Scale", std::array{ 0.0f, 0.0f }, std::array{ 2.0f, 2.0f }, std::array{ 1.0f, 1.0f });
        std::shared_ptr<UI::Slider1f> rotation = std::make_shared<UI::Slider1f>("Rotation", std::array{ -glm::pi<float>() }, std::array{ glm::pi<float>() }, std::array{ 0.0f });

        std::shared_ptr<UI::Text> text = std::make_shared<UI::Text>("FPS: ");
        std::shared_ptr<UI::ColorPicker4> clearColor = std::make_shared<UI::ColorPicker4>("Clear Color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        std::shared_ptr<UI::ColorPicker4> fragmentColor = std::make_shared<UI::ColorPicker4>("Fragment Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        renderer->SetClearColor(clearColor->GetColor());
        window->SetVSync(true);

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
        uiWindow.AddWidget(cameraPosition);
        uiWindow.AddWidget(cameraRotation);
        uiWindow.AddWidget(translation);
        uiWindow.AddWidget(scale);
        uiWindow.AddWidget(rotation);

        renderer->Add2DRenderable(object);

        while (window->IsOpen())
        {
            text->SetText("FPS: " + std::to_string(window->GetAverageFps()) + " (" + std::to_string(window->GetAverageFrameTime()) + "ms / frame)");

            if (clearColor->IsUpdated())
                renderer->SetClearColor(clearColor->GetColor());

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
                    renderer->SetWireframeMode(true);
                }
                else
                {
                    wireframe->SetText("Wireframe: Off");
                    renderer->SetWireframeMode(false);
                }
            }

            if (vsyncButton->IsPressed())
            {
                vsync = !vsync;
                if (vsync)
                {
                    vsyncButton->SetText("VSync: On");
                    window->SetVSync(true);
                }
                else
                {
                    vsyncButton->SetText("VSync: Off");
                    window->SetVSync(false);
                }
            }

            if (cameraPosition->IsUpdated())
                camera.Set2DPosition(glm::vec2(cameraPosition->GetValue()[0], cameraPosition->GetValue()[1]));

            if (cameraRotation->IsUpdated())
                camera.Set2DRotation(cameraRotation->GetValue()[0]);

            if (translation->IsUpdated())
                object->GetTransformRef().SetTranslation(glm::dvec2(translation->GetValue()[0], translation->GetValue()[1]));

            if (scale->IsUpdated())
                object->GetTransformRef().SetScale(glm::dvec2(scale->GetValue()[0], scale->GetValue()[1]));

            if (rotation->IsUpdated())
                object->GetTransformRef().SetRotation(rotation->GetValue()[0]);

            renderer->Clear();
            if (brick->GetTextureId().has_value())
                TextureManager::Bind2DTexture(brick->GetTextureId().value(), 1);
            renderer->Render(camera);

            renderer->RenderUIWindow(uiWindow);

            window->OnFrame();
        }
    }
}
