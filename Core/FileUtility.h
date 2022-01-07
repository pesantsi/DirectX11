#pragma once

#include <pch.h>

#include <fstream>
#include <vector>

namespace CoreProject
{
    typedef std::shared_ptr<std::vector<::byte>> ByteArray;

    class FileUtility
    {
    public:
        static void SetupRoot(LPWSTR* argv);
        static const std::wstring& GetRoot();
        static ByteArray ReadFileSync(const std::wstring& fileName);

    private:
        static std::wstring m_root;
    };
}
