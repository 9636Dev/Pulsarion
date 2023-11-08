#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include <variant>
#include <optional>

namespace Pulsarion
{
    template<typename T, typename F>
    class Result
    {
    public:
        struct OkTag {};
        struct FailTag {};

        inline static Result<T, F> Ok(const T& value)
        {
            return Result(value, OkTag{});
        }

        inline static Result<T, F> Fail(const F& failure)
        {
            return Result(failure, FailTag{});
        }

        inline Result(const T& value, const OkTag& tag = {})
        {
            m_Value = std::move(value);
            m_IsSuccess = true;
        }

        inline Result(const F& failure, const FailTag& tag = {})
        {
            m_Value = std::move(failure);
            m_IsSuccess = false;
        }

        inline bool IsSuccess() const noexcept
        {
            return m_IsSuccess;
        }

        inline bool IsFailure() const noexcept
        {
            return !m_IsSuccess;
        }


        inline const std::optional<T> Get() noexcept
        {
            if (m_IsSuccess)
            {
                static_assert(std::is_copy_constructible_v<T>, "[Result] Type 'T' must be copy constructible!");
                return std::make_optional<T>(std::get<T>(m_Value));
            }
            else return std::nullopt;
        }

        inline std::optional<F> GetFailure() noexcept
        {
            if (!m_IsSuccess)
            {
                static_assert(std::is_copy_constructible_v<F>, "[Result] Type 'F' must be copy constructible!");
                return std::make_optional<F>(std::get<F>(m_Value));
            }
            else return std::nullopt;
        }

    private:
        std::variant<T, F> m_Value;
        bool m_IsSuccess;
    };
}
