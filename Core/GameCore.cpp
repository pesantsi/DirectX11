#include "pch.h"

#include "GameCore.h"

namespace GameCore
{
    extern void ExitGame() noexcept;

    using namespace DirectX;

    using Microsoft::WRL::ComPtr;

    GameCore::GameCore() noexcept(false)
    {
        m_deviceResources = std::make_unique<DX::DeviceResources>();
        m_deviceResources->RegisterDeviceNotify(this);
    }

    // Initialize the Direct3D resources required to run.
    void GameCore::Initialize(HWND window, int width, int height)
    {
        m_deviceResources->SetWindow(window, width, height);

        m_deviceResources->CreateDeviceResources();
        CreateDeviceDependentResources();

        m_deviceResources->CreateWindowSizeDependentResources();
        CreateWindowSizeDependentResources();

        // TODO: Change the timer settings if you want something other than the default variable timestep mode.
        // e.g. for 60 FPS fixed timestep update logic, call:
        /*
        m_timer.SetFixedTimeStep(true);
        m_timer.SetTargetElapsedSeconds(1.0 / 60);
        */
    }

#pragma region Frame Update
    // Executes the basic game loop.
    void GameCore::Tick()
    {
        m_timer.Tick([&]()
            {
                Update(m_timer);
            });

        Render();
    }

    // Updates the world.
    void GameCore::Update(DX::StepTimer const& timer)
    {
        float elapsedTime = float(timer.GetElapsedSeconds());

        // TODO: Add your game logic here.
        elapsedTime;
    }
#pragma endregion

#pragma region Frame Render
    // Draws the scene.
    void GameCore::Render()
    {
        // Don't try to render anything before the first Update.
        if (m_timer.GetFrameCount() == 0)
        {
            return;
        }

        Clear();

        m_deviceResources->PIXBeginEvent(L"Render");
        auto context = m_deviceResources->GetD3DDeviceContext();

        // TODO: Add your rendering code here.
        context;

        m_deviceResources->PIXEndEvent();

        // Show the new frame.
        m_deviceResources->Present();
    }

    // Helper method to clear the back buffers.
    void GameCore::Clear()
    {
        m_deviceResources->PIXBeginEvent(L"Clear");

        // Clear the views.
        auto context = m_deviceResources->GetD3DDeviceContext();
        auto renderTarget = m_deviceResources->GetRenderTargetView();
        auto depthStencil = m_deviceResources->GetDepthStencilView();

        context->ClearRenderTargetView(renderTarget, Colors::AliceBlue);
        context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
        context->OMSetRenderTargets(1, &renderTarget, depthStencil);

        // Set the viewport.
        auto viewport = m_deviceResources->GetScreenViewport();
        context->RSSetViewports(1, &viewport);

        m_deviceResources->PIXEndEvent();
    }
#pragma endregion

#pragma region Message Handlers
    // Message handlers
    void GameCore::OnActivated()
    {
        // TODO: Game is becoming active window.
    }

    void GameCore::OnDeactivated()
    {
        // TODO: Game is becoming background window.
    }

    void GameCore::OnSuspending()
    {
        // TODO: Game is being power-suspended (or minimized).
    }

    void GameCore::OnResuming()
    {
        m_timer.ResetElapsedTime();

        // TODO: Game is being power-resumed (or returning from minimize).
    }

    void GameCore::OnWindowMoved()
    {
        auto r = m_deviceResources->GetOutputSize();
        m_deviceResources->WindowSizeChanged(r.right, r.bottom);
    }

    void GameCore::OnWindowSizeChanged(int width, int height)
    {
        if (!m_deviceResources->WindowSizeChanged(width, height))
            return;

        CreateWindowSizeDependentResources();

        // TODO: Game window is being resized.
    }

    // Properties
    void GameCore::GetDefaultSize(int& width, int& height) const noexcept
    {
        // TODO: Change to desired default window size (note minimum size is 320x200).
        width = 800;
        height = 600;
    }
#pragma endregion

#pragma region Direct3D Resources
    // These are the resources that depend on the device.
    void GameCore::CreateDeviceDependentResources()
    {
        auto device = m_deviceResources->GetD3DDevice();

        // TODO: Initialize device dependent objects here (independent of window size).
        device;
    }

    // Allocate all memory resources that change on a window SizeChanged event.
    void GameCore::CreateWindowSizeDependentResources()
    {
        // TODO: Initialize windows-size dependent objects here.
    }

    void GameCore::OnDeviceLost()
    {
        // TODO: Add Direct3D resource cleanup here.
    }

    void GameCore::OnDeviceRestored()
    {
        CreateDeviceDependentResources();

        CreateWindowSizeDependentResources();
    }
#pragma endregion
}