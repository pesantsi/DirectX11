#pragma once

#include <pch.h>
#include <unordered_map>
#include <string>
#include <sstream>

namespace CoreProject
{
    class CommandLineArgs
    {
    public:
        static void Initialize(int argc, wchar_t** argv);
        static bool GetInteger(const wchar_t* key, uint32_t& value);
        static bool GetFloat(const wchar_t* key, float& value);
        static bool GetString(const wchar_t* key, std::wstring& value);
    };
}