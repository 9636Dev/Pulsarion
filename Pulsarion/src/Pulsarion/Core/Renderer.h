#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include "Camera.h"

#include <glm/vec4.hpp>
#include <memory>


namespace Pulsarion
{
    class MeshBackend2D;
    class Mesh2D;

    namespace UI
    {
        class Window;
    }

    struct RenderInfo
    {
        std::size_t DrawCalls = 0;
        std::size_t Vertices = 0;
        std::size_t Indices = 0;
        std::size_t Instances = 0;
        std::size_t TimeMicroseconds = 0;

        void Clear()
        {
            DrawCalls = 0;
            Vertices = 0;
            Indices = 0;
            Instances = 0;
            TimeMicroseconds = 0;
        }
    };

    class GraphicalObject2D;

    class PULSARION_API Renderer
    {
    public:
        virtual ~Renderer() = default;

        /// <summary>
        /// Sets a renderer setting for wireframe mode, bypasses all other individual settings.
        /// </summary>
        /// <param name="wireframe">Set to true for wireframe, false for normal rendering.</param>
        virtual void SetWireframeMode(bool wireframe) = 0;
        /// <summary>
        /// Enables or disables blending.
        /// </summary>
        /// <param name="blend">Set to true for blending, false for no blend.</param>
        virtual void SetBlend(bool blend) = 0;
        /// <summary>
        /// Clears the screen.
        /// </summary>
        virtual void Clear() = 0;
        /// <summary>
        /// Sets the clear color (Default: Black).
        /// </summary>
        /// <param name="color">Clear color as floats, where rgba are between 0 and 1.</param>
        virtual void SetClearColor(glm::vec4 color) = 0;

        /// <summary>
        /// Renders a UI window.
        /// </summary>
        /// <param name="window">UI Window to render.</param>
        virtual void RenderUIWindow(const UI::Window& window) = 0;
        virtual void Add2DRenderable(std::shared_ptr<GraphicalObject2D> renderable) = 0;
        virtual bool Remove2DRenderable(std::shared_ptr<GraphicalObject2D> renderable) = 0;

        virtual void Set2DProjection(const glm::mat4& projection) = 0;
        virtual const glm::mat4& Get2DProjection() const = 0;

        /// <summary>
        /// Renders the scene with the given camera.
        /// </summary>
        /// <param name="camera">Camera to render the scene using.</param>
        virtual void Render(const Camera& camera) = 0;

        virtual const RenderInfo& GetRenderInfo() const = 0;

        // Utility Functions
    protected:
        static MeshBackend2D* GetMeshBackend2D(std::shared_ptr<Mesh2D>& mesh);
    };

    /// <summary>
    /// Creates a new renderer.
    /// </summary>
    /// <returns>A renderer pointer, the implementation is decided based on the rendering backend</returns>
    extern PULSARION_API std::unique_ptr<Renderer> CreateRenderer();
}
