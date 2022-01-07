#pragma once

#include <Windows.h>

namespace CoreProject_API
{
    interface IStepTimer
    {
    public:
        virtual double GetElapsedSeconds() const noexcept = 0;
    };
}
