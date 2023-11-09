#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include <variant>
#include <optional>

namespace Pulsarion
{
    struct OkTag {};
    struct FailTag {};

    template<typename T, typename F>
    class Result
    {
    public:
        inline static Result<T, F> Ok(const T& value)
        {
            return Result(value, OkTag{});
        }

        inline static Result<T, F> Fail(const F& failure)
        {
            return Result(failure, FailTag{});
        }

        inline explicit Result(const T& value, [[maybe_unused]] const OkTag& tag = {})
        {
            m_Value = std::move(value);
            m_IsSuccess = true;
        }

        inline explicit Result(const F& failure, [[maybe_unused]] const FailTag& tag = {})
        {
            m_Value = std::move(failure);
            m_IsSuccess = false;
        }

        [[nodiscard]] inline bool IsSuccess() const noexcept
        {
            return m_IsSuccess;
        }

        [[nodiscard]] inline bool IsFailure() const noexcept
        {
            return !m_IsSuccess;
        }


        inline std::optional<T> Get() noexcept
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

    // Same type
    template <typename T>
    class Result<T, T> {
        // Same function, just store data, and not std::variant
    public:
        inline static Result<T, T> Ok(const T& value)
        {
            return Result(value, true);
        }

        inline static Result<T, T> Fail(const T& failure) {
            return Result(failure, false);
        }

        inline Result(const T& value, bool isSuccess)
        {
            m_Value = std::move(value);
            m_IsSuccess = isSuccess;
        }

        inline Result(const T& value, const OkTag& tag = {}) : Result(value, true)
        {

        }

        inline Result(const T& value, const FailTag& tag = {}) : Result(value, false)
        {

        }

        [[nodiscard]] inline bool IsSuccess() const noexcept
        {
            return m_IsSuccess;
        }

        [[nodiscard]] inline bool IsFailure() const noexcept
        {
            return !m_IsSuccess;
        }

        std::optional<T> Get() noexcept
        {
            if (m_IsSuccess)
            {
                static_assert(std::is_copy_constructible_v<T>, "[Result] Type 'T' must be copy constructible!");
                return std::make_optional<T>(m_Value);
            }
            else return std::nullopt;
        }

        std::optional<T> GetFailure() noexcept
        {
            if (!m_IsSuccess)
            {
                static_assert(std::is_copy_constructible_v<T>, "[Result] Type 'T' must be copy constructible!");
                return std::make_optional<T>(m_Value);
            }
            else return std::nullopt;
        }

    private:
        T m_Value;
        bool m_IsSuccess;
    };
}
