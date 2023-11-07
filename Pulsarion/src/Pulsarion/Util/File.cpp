#include "Pulsarionpch.h"
#include "File.h"

namespace Pulsarion
{
    File::File(const std::string& path)
        : m_Path(path), m_Content(), m_CacheContent(false)
    {

    }

    File::~File()
    {

    }

    File::File(const File& other) noexcept
        : m_Path(other.m_Path), m_CacheContent(other.m_CacheContent)
    {
        if (other.m_Content.has_value())
        {
            m_Content = std::make_optional<Modifiable<std::string>>(other.m_Content->GetConst());
        }
        else m_Content = std::optional();
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
        else m_Content = std::optional();
        return *this;
    }

    File& File::operator=(File&& other) noexcept
    {
        m_Path = std::move(other.m_Path);
        m_Content = std::move(other.m_Content);
        return *this;
    }

    const std::string& File::GetPath() const noexcept
    {
        return m_Path;
    }

    std::string File::GetContent(bool ignoreCached) const
    {
        if (!m_Content.has_value() || ignoreCached)
        {
            std::ifstream file(m_Path);
            if (!file.is_open())
            {
                PLS_LOG_ERROR("Failed to open file: {0}", m_Path);
                return ""; // TODO: Throw exception
            }
            std::stringstream ss;
            ss << file.rdbuf();
            file.close();
            if (m_CacheContent)
                m_Content->Set(ss.str());
            else
                return ss.str();
        }
        return m_Content->GetConst();
    }

    void File::UpdateContent() const {
        if (!m_Content.has_value() || !m_Content->IsDirty()) return;
        WriteContent(m_Content->GetConst());
        m_Content->SetDirty(false);
    }

    void File::SetContent(const std::string& content)
    {
        if (m_CacheContent)
            m_Content = Modifiable<std::string>(content);
        else
            WriteContent(content);
    }

    void File::WriteContent(const std::string& content) const
    {
        std::ofstream file(m_Path);
        if (!file.is_open())
        {
            PLS_LOG_ERROR("Failed to open file: {0}", m_Path);
            return; // TODO: Throw exception
        }
        file << content;
        file.close();
    }

    void File::AppendContent(const std::string& content)
    {
        if (m_CacheContent)
            m_Content->Get() = m_Content->GetConst() + content;
        else
            SetContent(m_Content->GetConst() + content);
    }

    bool File::Exists() const noexcept
    {
        std::ifstream file(m_Path);
        return file.good();
    }

    bool File::CreateFile() const
    {
        if (Exists()) return false;
        std::ofstream file(m_Path);
        if (!file.is_open())
        {
            PLS_LOG_ERROR("Failed to create file: {0}", m_Path);
            return false;
        }
        file.close();
        return true;
    }

    bool File::DeleteFile() const
    {
        if (!Exists()) return false;
        if (std::remove(m_Path.c_str()) == -1)
        {
            PLS_LOG_ERROR("Failed to delete file: {0}", m_Path);
            return false;
        }
        return true;
    }

    void File::CacheContent(bool cache)
    {
        if (m_CacheContent && !cache)
            UpdateContent();
        m_CacheContent = cache;
    }
}
