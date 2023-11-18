#include "Pulsarionpch.h"
#include "Debug.h"

#include "Pulsarion/Core/Renderer.h"

namespace Pulsarion
{
    template<>
    std::string Debug::ToString(const glm::vec2& value)
    {
        return std::string("Vec2(" + std::to_string(value.x) + ", " + std::to_string(value.y) + ")");
    }

    template<>
    std::string Debug::ToString(const glm::vec3& value)
    {
        return std::string("Vec3(" + std::to_string(value.x) + ", " + std::to_string(value.y) + ", " + std::to_string(value.z) + ")");
    }

    template<>
    std::string Debug::ToString(const glm::vec4& value)
    {
        return std::string("Vec4(" + std::to_string(value.x) + ", " + std::to_string(value.y) + ", " + std::to_string(value.z) + ", " + std::to_string(value.w) + ")");
    }

    template<>
    std::string Debug::ToString(const glm::mat4& value)
    {
        return std::string("Mat4(" + std::to_string(value[0][0]) + ", " + std::to_string(value[0][1]) + ", " + std::to_string(value[0][2]) +", " + std::to_string(value[0][3]) + ", " + std::to_string(value[1][0]) + ", " + std::to_string(value[1][1]) + ", " + std::to_string(value[1][2]) + ", " + std::to_string(value[1][3]) + ", " + std::to_string(value[2][0]) + ", " + std::to_string(value[2][1]) + ", " + std::to_string(value[2][2]) + ", " + std::to_string(value[2][3]) + ", " + std::to_string(value[3][0]) + ", " + std::to_string(value[3][1]) + ", " + std::to_string(value[3][2]) + ", " + std::to_string(value[3][3]) + ")");
    }

    template<>
    std::string Debug::ToString(const glm::quat& value)
    {
        return std::string("Quat(" + std::to_string(value.x) + ", " + std::to_string(value.y) + ", " + std::to_string(value.z) + ", " + std::to_string(value.w) + ")");
    }

    template<>
    std::string Debug::ToString(const RenderInfo& value)
    {
        return std::string("RenderInfo(DrawCalls: " + std::to_string(value.DrawCalls) + ", Vertices: " + std::to_string(value.Vertices) + ", Indices: " + std::to_string(value.Indices) + ", Instances: " + std::to_string(value.Instances) + ", TimeMicroseconds: " + std::to_string(value.TimeMicroseconds) + ")");
    }
}
