#include "Pulsarionpch.h"
#include "File.h"

#include <system_error>

namespace Pulsarion
{
    File::File(const std::string& path, bool absolute)
        : m_CacheContent(false), m_Content(std::nullopt)
    {
        if (absolute)
        {
            m_Path = std::filesystem::absolute(path);
        }
        else
        {
            m_Path = std::filesystem::relative(path);
        }
    }

    File::~File()
    {
        (void)UpdateContent();
    }

    File::File(const File& other)
        : m_Path(other.m_Path), m_CacheContent(other.m_CacheContent)
    {
        if (other.m_Content.has_value())
        {
            m_Content = std::make_optional<Modifiable<std::string>>(other.m_Content->GetConst());
        }
        else m_Content = std::optional<Modifiable<std::string>>();
    }

    File::File(File&& other)
        : m_Path(std::move(other.m_Path)), m_Content(std::move(other.m_Content)), m_CacheContent(other.m_CacheContent)
    {

    }

    File& File::operator=(const File& other)
    {
        m_Path = other.m_Path;
        m_CacheContent = other.m_CacheContent;
        if (other.m_Content.has_value())
        {
            m_Content = std::make_optional<Modifiable<std::string>>(other.m_Content->GetConst());
        }
        else m_Content = std::nullopt;
        return *this;
    }

    File& File::operator=(File&& other)
    {
        m_Path = std::move(other.m_Path);
        m_Content = std::move(other.m_Content);
        return *this;
    }

    std::filesystem::path File::GetAbsolutePath() const
    {
        if (m_Path.is_absolute())
        {
            return m_Path;
        }
        else
        {
            return std::filesystem::absolute(m_Path);
        }
    }

    std::optional<std::filesystem::path> File::GetRelativePath() const
    {
        if (m_Path.is_relative())
            return m_Path;
        
        else if (m_Path.has_relative_path())
            return std::filesystem::relative(m_Path);
        return std::nullopt;
    }

    std::string File::GetFileName() const
    {
        return m_Path.filename().string();
    }

    std::string File::GetFileNameWithoutExtension() const
    {
        return m_Path.stem().string();
    }

    std::string File::GetExtension() const
    {
        if (m_Path.has_extension())
            return m_Path.extension().string();
        return "";
    }

    bool File::IsDirectory() const
    {
        return std::filesystem::is_directory(m_Path);
    }

    bool File::IsFile() const
    {
        return std::filesystem::is_regular_file(m_Path);
    }

    bool File::Exists() const
    {
        return std::filesystem::exists(m_Path);
    }

    File File::GetParent() const
    {
        return File(m_Path.parent_path().string());
    }

    Result<bool, std::error_code> File::CreateDirectories() const
    {
        std::error_code errorCode;    
        bool result = std::filesystem::create_directories(m_Path, errorCode);
        if (errorCode.value() == 0)
            return Result<bool, std::error_code>::Ok(result);

        return Result<bool, std::error_code>::Fail(errorCode);
    }

    bool File::CreateNewFile() const
    {
        std::ofstream file(m_Path);
        if (file.good())
        {
            file.close();
            return true;
        }
        file.close();
        return false;
    }

    Result<bool, std::error_code> File::Delete() const
    {
        std::error_code errorCode;
        bool result = std::filesystem::remove(m_Path, errorCode);
        if (errorCode.value() == 0)
            return Result<bool, std::error_code>::Ok(result);

        return Result<bool, std::error_code>::Fail(errorCode);
    }

    std::optional<std::string> File::ReadFile() const
    {
        std::ifstream file(m_Path);
        if (!file.good())
        {
            file.close();
            return std::nullopt;
        }
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        return ss.str();
    }

    std::optional<std::string> File::GetContent() const
    {
        if (m_Content.has_value())
        {
            if (m_Content->IsDirty())
            {
                // Write changes to file
                if (!UpdateContent())
                {
                    return std::nullopt;
                }
                auto content = ReadFile();
                if (content.has_value())
                {
                    m_Content->Set(content.value());
                }
                else
                {
                    m_Content.reset();
                    return std::nullopt;
                }
            }
            return m_Content->GetConst();
        }
        auto content = ReadFile();
        if (!content.has_value())
            return std::nullopt;
        if (m_CacheContent)
        {
            m_Content = std::make_optional<Modifiable<std::string>>(content.value());
        }

        return content;
    }

    bool File::SetContent(const std::string& content)
    {
        if (m_CacheContent)
        {
            if (!m_Content.has_value())
                m_Content = std::make_optional<Modifiable<std::string>>(content);
            else
                m_Content->Set(content);
        }
        else
        {
            std::ofstream file(m_Path);
            if (!file.good())
            {
                file.close();
                return false;
            }
            file << content;
            file.close();
        }
        return true;
    }

    bool File::AppendContent(const std::string& content)
    {
        if (m_CacheContent)
        {
            if (!m_Content.has_value())
                m_Content = std::make_optional<Modifiable<std::string>>(content);
            else
                m_Content->Set(m_Content->GetConst() + content);
        }
        else
        {
            std::ofstream file(m_Path, std::ios_base::app);
            if (!file.good())
            {
                file.close();
                return false;
            }
            file << content;
            file.close();
        }
        return true;
    }

    bool File::ClearContent()
    {
        if (m_CacheContent)
        {
            if (!m_Content.has_value())
                m_Content = std::make_optional<Modifiable<std::string>>("");
            else
                m_Content->Set("");
        }
        else
        {
            std::ofstream file(m_Path);
            if (!file.good())
            {
                file.close();
                return false;
            }
            file.close();
        }
        return true;
    }

    bool File::UpdateContent() const
    {
        if (m_Content.has_value() && m_Content->IsDirty())
        {
            std::ofstream file(m_Path);
            file << m_Content->GetConst();
            file.close();
            m_Content->SetDirty(false);
            return true;
        }
        return false;
    }

    bool File::IsUsingCachedContent() const noexcept
    {
        return m_CacheContent;
    }

    void File::SetCacheContent(bool cache) noexcept
    {
        if (m_CacheContent && !cache)
        {
            if (!UpdateContent())
            {
                PLS_LOG_WARN("[File] Could not update file content!");
            }
            ClearCachedContent();
        }
        m_CacheContent = cache;
    }

    bool File::ClearCachedContent() const
    {
        if (m_Content.has_value())
        {
            m_Content.reset();
            return true;
        }
        return false;
    }
}
