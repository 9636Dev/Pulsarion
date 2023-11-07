#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Modifiable.h"

#include <string>
#include <optional>
#include <filesystem>

namespace Pulsarion
{
    class PULSARION_API File
    {
    public:
        File(const std::string& path, bool absolute = true);
        ~File();
        File(const File&) noexcept;
        File(File&&) noexcept;
        File& operator=(const File&) noexcept;
        File& operator=(File&&) noexcept;

        std::filesystem::path GetAbsolutePath() const noexcept;
        std::optional<std::filesystem::path> GetRelativePath() const noexcept;
        std::string GetFileName() const noexcept;
        bool IsDirectory() const noexcept;
        bool IsFile() const noexcept;
        bool Exists() const noexcept;
        std::string GetFileNameWithoutExtension() const noexcept;
        std::string GetExtension() const noexcept;
        File GetParent() const;
        bool CreateDirectories() const;
        bool CreateNewFile() const;
        bool Delete() const;

        std::string GetContent() const;
        void SetContent(const std::string& content);
        void AppendContent(const std::string& content);
        void ClearContent();
        void UpdateContent() const;
    private:
        std::filesystem::path m_Path;
        mutable std::optional<Modifiable<std::string>> m_Content;
        bool m_CacheContent;
    };
}
