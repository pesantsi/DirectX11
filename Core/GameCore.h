#pragma once

#include <pch.h>

#include <DeviceResources.h>
#include <GameInput.h>
#include <IGameApp.h>
#include <StepTimer.h>

namespace CoreProject
{
    // A basic game implementation that creates a D3D11 device and
    // provides a game loop.
    class GameCore final : public CoreProject::IDeviceNotify
    {
    public:

        GameCore(IGameApp& app) noexcept(false);
        ~GameCore() = default;

        GameCore(GameCore&&) = default;
        GameCore& operator= (GameCore&&) = default;

        GameCore(GameCore const&) = delete;
        GameCore& operator= (GameCore const&) = delete;

        // Initialization and management
        void Initialize(HWND window, int width, int height);
        void Shutdown();

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

        void Update(CoreProject::StepTimer const& timer);
        void Render();

        void Clear();

        void CreateDeviceDependentResources();
        void CreateWindowSizeDependentResources();

        // Device resources.
        std::shared_ptr<CoreProject::DeviceResources> m_deviceResources;

        // Rendering loop timer.
        CoreProject::StepTimer m_timer;
        IGameApp* m_gameApp;
    };
}

namespace CoreProject
{
    int RunApplication(IGameApp& app, const wchar_t* className, HINSTANCE hInstance, int nCmdShow);
}

#define CREATE_APPLICATION( app_class ) \
    int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPWSTR /*lpCmdLine*/, _In_ int nCmdShow) \
    { \
        return CoreProject::RunApplication( app_class(), L#app_class, hInstance, nCmdShow ); \
    }