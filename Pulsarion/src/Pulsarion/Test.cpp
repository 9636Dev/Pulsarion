#include "Pulsarionpch.h"
#include "Core/Window.h"

#include "Test.h"

#include "Core/Backend/OpenGL/VertexArray.h"
#include "Core/Backend/OpenGL/VertexBuffer.h"
#include "Core/Backend/OpenGL/IndexBuffer.h"
#include "Core/Backend/OpenGL/Shader.h"

#include "Core/Renderer.h"

#include "GL/glew.h"

namespace Pulsarion
{
    using namespace OpenGL;

    void Test()
    {
        std::unique_ptr<Window> window = CreateWindowPointer(WindowProperties());
        window->SetEventCallback([](Event& event) { });
        std::unique_ptr<Renderer> renderer = CreateRenderer();
        VertexArray va;
        VertexBuffer vb;
        float vertices[6] = {
            -0.5f, -0.5f,
             0.0f,  0.5f,
             0.5f, -0.5f
        };
        vb.SetData(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        va.Bind();

        IndexBuffer ib;
        unsigned int indices[3] = { 0, 1, 2 };
        ib.SetData(indices, sizeof(indices));

        std::optional<Shader> vertexShaderOpt = Shader::FromFile(ShaderType::VertexShader, File("assets/shaders/basic_vertex.glsl"));
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
        std::optional<Shader> fragmentShaderOpt = Shader::FromFile(ShaderType::FragmentShader, File("assets/shaders/basic_fragment.glsl"));
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

        program.Use();
        renderer->SetClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
        window->SetVSync(true);

        while (window->IsOpen())
        {
            renderer->Clear();
            va.Bind();
            program.Use();
            ib.Bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            window->OnFrame();
        }
    }
}
