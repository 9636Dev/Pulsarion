#include "Pulsarionpch.h"
#include "File.h"

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
        UpdateContent();
    }

    File::File(const File& other) noexcept
        : m_Path(other.m_Path), m_CacheContent(other.m_CacheContent)
    {
        if (other.m_Content.has_value())
        {
            m_Content = std::make_optional<Modifiable<std::string>>(other.m_Content->GetConst());
        }
        else m_Content = std::optional<Modifiable<std::string>>();
    }

    File::File(File&& other) noexcept
        : m_Path(std::move(other.m_Path)), m_Content(std::move(other.m_Content)), m_CacheContent(other.m_CacheContent)
    {

    }

    File& File::operator=(const File& other) noexcept
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

    File& File::operator=(File&& other) noexcept
    {
        m_Path = std::move(other.m_Path);
        m_Content = std::move(other.m_Content);
        return *this;
    }

    std::filesystem::path File::GetAbsolutePath() const noexcept
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

    std::optional<std::filesystem::path> File::GetRelativePath() const noexcept
    {
        if (m_Path.is_relative())
            return m_Path;
        
        else if (m_Path.has_relative_path())
            return std::filesystem::relative(m_Path);
        return std::nullopt;
    }

    std::string File::GetFileName() const noexcept
    {
        return m_Path.filename().string();
    }

    std::string File::GetFileNameWithoutExtension() const noexcept
    {
        return m_Path.stem().string();
    }

    std::string File::GetExtension() const noexcept
    {
        if (m_Path.has_extension())
            return m_Path.extension().string();
        return "";
    }

    bool File::IsDirectory() const noexcept
    {
        return std::filesystem::is_directory(m_Path);
    }

    bool File::IsFile() const noexcept
    {
        return std::filesystem::is_regular_file(m_Path);
    }

    bool File::Exists() const noexcept
    {
        return std::filesystem::exists(m_Path);
    }

    File File::GetParent() const
    {
        return File(m_Path.parent_path().string());
    }

    bool File::CreateDirectories() const
    {
        try {
            return std::filesystem::create_directories(m_Path);
        }
        catch (std::filesystem::filesystem_error& e)
        {
            PLS_LOG_WARN("File::CreateDirectories Error: {}", e.what());
            return false;
        }
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

    bool File::Delete() const
    {
        return std::filesystem::remove(m_Path);
    }

    std::string File::GetContent() const
    {
        if (m_Content.has_value())
        {
            return m_Content->GetConst();
        }

        std::ifstream file(m_Path);
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        std::string content = ss.str();
        if (m_CacheContent)
        {
            m_Content = std::make_optional<Modifiable<std::string>>(content);
        }

        return content;
    }

    void File::SetContent(const std::string& content)
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
            file << content;
            file.close();
        }
    }

    void File::AppendContent(const std::string& content)
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
            file << content;
            file.close();
        }
    }

    void File::ClearContent()
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
            file.close();
        }
    }

    void File::UpdateContent() const
    {
        if (m_Content.has_value() && m_Content->IsDirty())
        {
            std::ofstream file(m_Path);
            file << m_Content->GetConst();
            file.close();
            m_Content->SetDirty(false);
        }
    }
}
