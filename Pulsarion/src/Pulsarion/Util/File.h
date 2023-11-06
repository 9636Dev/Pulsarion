#pragma once

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
            const std::string& GetContent() const;
            void SetContent(const std::string& content);
            void AppendContent(const std::string& content);

            bool Exists() const noexcept;
            bool CreateFile() const;
            bool DeleteFile() const;
    };
}
