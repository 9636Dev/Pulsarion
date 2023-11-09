#pragma once

#include <forward_list>

namespace Pulsarion {

    template<typename T>
    class Modifiable {
    public:
        template <typename... Args>
        static Modifiable<T> Create(Args&&... args)
        {
            T value(std::forward<Args>(args)...);
            Modifiable<T> temp =  Modifiable<T>(std::move(value));
            temp.SetDirty(true);
            return temp;
        }

        
        inline Modifiable(T value)
            : m_Value(value), m_Dirty(false)
        {

        }

        inline ~Modifiable()
        {

        }

        Modifiable(const Modifiable&) = delete;
        inline Modifiable(Modifiable&& other) : m_Value(std::move(other.m_Value)), m_Dirty(other.m_Dirty)
        {

        }
        Modifiable& operator=(const Modifiable&) = delete;
        inline Modifiable& operator=(Modifiable&& other)
        {
            m_Value = std::move(other.m_Value);
            m_Dirty = other.m_Dirty;
            return *this;
        }

        inline T& Get() noexcept
        {
            SetDirty();
            return m_Value;
        }

        inline const T& GetConst() const noexcept
        {
            return m_Value;
        }

        inline void Set(const T& value) noexcept
        {
            m_Value = value;
            SetDirty();
        }

        inline void Set(T&& value) noexcept
        {
            m_Value = std::move(value);
            SetDirty();
        }

        inline bool IsDirty() const noexcept
        {
            return m_Dirty;
        }

        inline void SetDirty(bool dirty = true) noexcept
        {
            m_Dirty = dirty;
        }
    private:

        T m_Value;
        bool m_Dirty;
    };
    
}
