#pragma once

#include "pch.h"

#include <fstream>

namespace CoreProject
{
    typedef std::shared_ptr<std::vector<::byte>> ByteArray;

    class FileUtility
    {
    public:
        static void SetupRoot(LPWSTR* argv);
        static const std::wstring& GetRoot();
        static ByteArray ReadFileSync(const std::wstring& fileName);
        static void* LoadShaderFile(const std::wstring& fileName, long* len);

    private:
        static std::wstring m_root;
    };
}
