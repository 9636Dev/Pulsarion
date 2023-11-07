#pragma once

#include "Modifiable.h"

#include <string>

namespace Pulsarion
{
    class File
    {
        public:
            File(const std::string& path);
            ~File();
            File(const File&) noexcept;
            File(File&&) noexcept;
            File& operator=(const File&) noexcept;
            File& operator=(File&&) noexcept;

            const std::string& GetPath() const noexcept;
            std::string GetContent(bool ignoreCached = false) const;
            void SetContent(const std::string& content);
            void AppendContent(const std::string& content);

            bool Exists() const noexcept;
            bool CreateFile() const;
            bool DeleteFile() const;
            void CacheContent(bool cache = true);
            void UpdateContent() const;
    private:
        void WriteContent(const std::string& content) const;

        bool m_CacheContent;
        std::string m_Path;
        mutable std::optional<Modifiable<std::string>> m_Content;
    };
}
