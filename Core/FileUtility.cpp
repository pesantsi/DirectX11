#include "pch.h"

#include "FileUtility.h"

namespace CoreProject
{
    ByteArray NullFile = std::make_shared<std::vector<byte> >(std::vector<byte>());
    std::wstring FileUtility::m_root = L"";

    ByteArray FileUtility::ReadFileSync(const std::wstring& fileName)
    {
        std::wstring fullFileName = m_root + fileName;

        struct _stat64 fileStat;
        int fileExists = _wstat64(fullFileName.c_str(), &fileStat);
        if (fileExists == -1)
            return NullFile;

        std::ifstream file(fullFileName, std::ios::in | std::ios::binary);
        if (!file)
            return NullFile;

        CoreProject::ByteArray byteArray = std::make_shared<std::vector<byte>>(fileStat.st_size);
        file.read((char*)byteArray->data(), byteArray->size());
        file.close();

        return byteArray;
    }

    void FileUtility::SetupRoot(LPWSTR* argv)
    {
        std::wstring filename(*argv);

        const size_t last_slash_idx = filename.rfind('\\');
        if (std::string::npos != last_slash_idx)
        {
            m_root = filename.substr(0, last_slash_idx + 1);
        }
    }

    const std::wstring& FileUtility::GetRoot()
    {
        return m_root;
    }
}
