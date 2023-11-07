#pragma once

namespace Pulsarion {

    template<typename T>
    class Modifiable {
    public:
        template <typename... Args>
        Modifiable(Args&&... args)
            : m_Value(std::forward<Args>(args)...), m_Dirty(false)
        {

        }

        ~Modifiable()
        {

        }

        Modifiable(const Modifiable&) = delete;
        Modifiable(Modifiable&&) : m_Value(std::move(other.m_Value)), m_Dirty(other.m_Dirty)
        {

        }
        Modifiable& operator=(const Modifiable&) = delete;
        Modifiable& operator=(Modifiable&&)
        {
            m_Value = std::move(other.m_Value);
            m_Dirty = other.m_Dirty;
            return *this;
        }

        T& Get() noexcept
        {
            SetDirty();
            return m_Value;
        }

        const T& GetConst() const noexcept
        {
            return m_Value;
        }

        void Set(const T& value) noexcept
        {
            m_Value = value;
            SetDirty();
        }

        void Set(T&& value) noexcept
        {
            m_Value = std::move(value);
            SetDirty();
        }

        bool IsDirty() const noexcept
        {
            return m_Dirty;
        }

        void SetDirty(bool dirty = true) noexcept
        {
            m_Dirty = dirty;
        }

        template<typename T>
        static Modifiable<T> Emplace(T&& value)
        {
            return Modifiable<T>(value);
        }

        inline explicit operator T&() noexcept { return Get(); }
        inline operator const T&() const noexcept { return GetConst(); };
    private:
        Modifiable(T&& value)
                : m_Value(std::move(value)), m_Dirty(false)
        {

        }

        T m_Value;
        bool m_Dirty;
    };

}