#pragma once

#include <Windows.h>

namespace CoreProject_API
{
    interface IDeviceResources
    {
    public:
        // Device Accessors.
        virtual RECT GetOutputSize() const noexcept = 0;

        // Direct3D Accessors.
        virtual ID3D11Device1* GetD3DDevice() const noexcept = 0;
        virtual ID3D11DeviceContext1* GetD3DDeviceContext() const noexcept = 0;
    };
}
