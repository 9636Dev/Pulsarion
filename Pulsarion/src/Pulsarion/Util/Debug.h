#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>

namespace Pulsarion
{
    struct RenderInfo;

    class PULSARION_API Debug
    {
    public:
        template<typename T>
        static std::string ToString(const T& value)
        {
            return std::string("Not implemented");
        }
    };

    template<>
    PULSARION_API std::string Debug::ToString(const glm::vec2& value);
    template<>
    PULSARION_API std::string Debug::ToString(const glm::vec3& value);
    template<>
    PULSARION_API std::string Debug::ToString(const glm::vec4& value);
    template<>
    PULSARION_API std::string Debug::ToString(const glm::mat4& value);
    template<>
    PULSARION_API std::string Debug::ToString(const glm::quat& value);
    template<>
    PULSARION_API std::string Debug::ToString(const RenderInfo& value);


}
