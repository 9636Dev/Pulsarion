#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Modifiable.h"

#include "Result.h"

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
        File(const File&);
        File(File&&);
        File& operator=(const File&);
        File& operator=(File&&);

        [[nodiscard]] std::filesystem::path GetAbsolutePath() const;
        [[nodiscard]] std::optional<std::filesystem::path> GetRelativePath() const;
        [[nodiscard]] std::string GetFileName() const;
        [[nodiscard]] bool IsDirectory() const;
        [[nodiscard]] bool IsFile() const;
        [[nodiscard]] bool Exists() const;
        [[nodiscard]] std::string GetFileNameWithoutExtension() const;
        [[nodiscard]] std::string GetExtension() const;
        [[nodiscard]] File GetParent() const;
        [[nodiscard]] Result<bool, std::error_code> CreateDirectories() const;
        [[nodiscard]] bool CreateNewFile() const;
        [[nodiscard]] Result<bool, std::error_code> Delete() const;

        [[nodiscard]] std::optional<std::string> GetContent() const;
        [[nodiscard]] bool SetContent(const std::string& content);
        [[nodiscard]] bool AppendContent(const std::string& content);
        [[nodiscard]] bool ClearContent();
        [[nodiscard]] bool UpdateContent() const;

        bool IsUsingCachedContent() const noexcept;
        void SetCacheContent(bool cache) noexcept;
        /// <summary>
        /// Clears the cached content, without calling UpdateContent().
        /// </summary>
        /// <returns>Whether of not the content was cleared. (False if not using cache)</returns>
        bool ClearCachedContent() const;
    private:
        [[nodiscard]] std::optional<std::string> ReadFile() const;

        std::filesystem::path m_Path;
        mutable std::optional<Modifiable<std::string>> m_Content;
        bool m_CacheContent;
    };
}
