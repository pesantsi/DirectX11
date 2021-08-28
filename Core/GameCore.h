#pragma once

#include "pch.h"

#include "IGameApp.h"
#include "DeviceResources.h"
#include "StepTimer.h"

namespace GameCore
{
    // A basic game implementation that creates a D3D11 device and
    // provides a game loop.
    class GameCore final : public DX::IDeviceNotify
    {
    public:

        GameCore() noexcept(false);
        ~GameCore() = default;

        GameCore(GameCore&&) = default;
        GameCore& operator= (GameCore&&) = default;

        GameCore(GameCore const&) = delete;
        GameCore& operator= (GameCore const&) = delete;

        // Initialization and management
        void Initialize(HWND window, int width, int height);

        // Basic game loop
        void Tick();

        // IDeviceNotify
        void OnDeviceLost() override;
        void OnDeviceRestored() override;

        // Messages
        void OnActivated();
        void OnDeactivated();
        void OnSuspending();
        void OnResuming();
        void OnWindowMoved();
        void OnWindowSizeChanged(int width, int height);

        // Properties
        void GetDefaultSize(int& width, int& height) const noexcept;

    private:

        void Update(DX::StepTimer const& timer);
        void Render();

        void Clear();

        void CreateDeviceDependentResources();
        void CreateWindowSizeDependentResources();

        // Device resources.
        std::unique_ptr<DX::DeviceResources>    m_deviceResources;

        // Rendering loop timer.
        DX::StepTimer                           m_timer;
    };
}

namespace GameCore
{
    int RunApplication(IGameApp& app, const wchar_t* className, HINSTANCE hInst, int nCmdShow);
}

#define CREATE_APPLICATION( app_class ) \
    int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPWSTR /*lpCmdLine*/, _In_ int nCmdShow) \
    { \
        return GameCore::RunApplication( app_class(), L#app_class, hInstance, nCmdShow ); \
    }

