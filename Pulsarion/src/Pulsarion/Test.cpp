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

#include "GL/glew.h"

namespace Pulsarion
{
    using namespace OpenGL;

    void Test()
    {
        std::unique_ptr<Window> window = CreateWindowPointer(WindowProperties());
        window->SetEventCallback([](Event& event) { });
        std::unique_ptr<Renderer> renderer = CreateRenderer();
        renderer->SetBlend(true);
        VertexArray va;
        VertexBuffer vb;
        float vertices[16] = {
            -0.5f,  0.5f, -1.0f, 1.0f,
             0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -1.0f, -1.0f,
             0.5f, -0.5f,  1.0f, -1.0f
        };
        vb.SetData(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        va.Bind();

        IndexBuffer ib;
        unsigned int indices[6] = { 0, 1, 2, 1, 2, 3 };
        ib.SetData(indices, sizeof(indices));

        std::optional<Shader> vertexShaderOpt = Shader::FromFile(ShaderType::VertexShader, File("assets/shaders/basic_textured_vertex.glsl"));
        if (!vertexShaderOpt)
        {
            PLS_LOG_ERROR("Failed to load vertex shader");
            return;
        }
        Shader vertexShader = std::move(vertexShaderOpt.value());

        if (!vertexShader.Compile())
        {
            PLS_LOG_ERROR("Failed to compile vertex shader: {}", vertexShader.GetInfoLog());
        }
        std::optional<Shader> fragmentShaderOpt = Shader::FromFile(ShaderType::FragmentShader, File("assets/shaders/basic_textured_fragment.glsl"));
        if (!fragmentShaderOpt)
        {
            PLS_LOG_ERROR("Failed to load fragment shader");
            return;
        }

        Shader fragmentShader = std::move(fragmentShaderOpt.value());
        if (!fragmentShader.Compile())
        {
            PLS_LOG_ERROR("Failed to compile fragment shader: {}", fragmentShader.GetInfoLog());
        }

        ShaderProgram program;
        program.AttachShader(vertexShader);
        program.AttachShader(fragmentShader);
        if (!program.Link())
        {
            PLS_LOG_ERROR("Failed to link shader program: {}", program.GetInfoLog());
        }

        Image brickImage(File("assets/textures/brick.png"));
        Texture texture;
        texture.DefaultSettings();
        texture.SetData(brickImage);
        texture.SetTextureUnit(TextureUnit::Texture0);

        program.Use();

        Transform2D transform;
        std::shared_ptr<UI::Slider2d> translation = std::make_shared<UI::Slider2d>("Translation", std::array<double, 2>({-1.0, -1.0}), std::array<double, 2>({1.0, 1.0}), std::array<double, 2>({0.0, 0.0}));
        std::shared_ptr<UI::Slider2d> scale = std::make_shared<UI::Slider2d>("Scale", std::array<double, 2>({ 0.0, 0.0 }), std::array<double, 2>({ 2.0, 2.0 }), std::array<double, 2>({ 1.0, 1.0 }));
        std::shared_ptr<UI::Slider1d> rotation = std::make_shared<UI::Slider1d>("Rotation", std::array<double, 1>({ - glm::pi<double>() }), std::array<double, 1>({ glm::pi<double>() }), std::array<double, 1>({ 0.0 }));

        renderer->SetClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
        window->SetVSync(true);

        std::shared_ptr<UI::Text> text = std::make_shared<UI::Text>("FPS: ");
        std::shared_ptr<UI::ColorPicker4> clearColor = std::make_shared<UI::ColorPicker4>("Clear Color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        std::shared_ptr<UI::ColorPicker4> fragmentColor = std::make_shared<UI::ColorPicker4>("Fragment Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        renderer->SetClearColor(clearColor->GetColor());
        program.SetUniform("u_Color", fragmentColor->GetColor());

        bool renderWireframe = false;
        std::shared_ptr<UI::Button> wireframe = std::make_shared<UI::Button>("Wireframe: Off");
        UI::Window uiWindow("Controls");
        uiWindow.AddWidget(text);
        uiWindow.AddWidget(clearColor);
        uiWindow.AddWidget(fragmentColor);
        uiWindow.AddWidget(wireframe);
        uiWindow.AddWidget(translation);
        uiWindow.AddWidget(scale);
        uiWindow.AddWidget(rotation);

        program.SetUniform("u_ModelMatrix", transform.GetAsMatrix());

        while (window->IsOpen())
        {
            text->SetText("FPS: " + std::to_string(window->GetAverageFps()) + " (" + std::to_string(window->GetAverageFrameTime()) + "ms / frame)");

            if (clearColor->IsUpdated())
                renderer->SetClearColor(clearColor->GetColor());

            if (fragmentColor->IsUpdated())
                program.SetUniform("u_Color", fragmentColor->GetColor());

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

            if (translation->IsUpdated())
                transform.SetTranslation(glm::dvec2(translation->GetValue()[0], translation->GetValue()[1]));
            
            if (scale->IsUpdated())
                transform.SetScale(glm::dvec2(scale->GetValue()[0], scale->GetValue()[1]));

            if (rotation->IsUpdated())
                transform.SetRotation(rotation->GetValue()[0]);

            if (transform.IsDirty())
                program.SetUniform("u_ModelMatrix", transform.GetAsMatrix());

            renderer->Clear();
            va.Bind();
            program.Use();
            texture.Bind();
            ib.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            renderer->RenderUIWindow(uiWindow);

            window->OnFrame();
        }
    }
}
