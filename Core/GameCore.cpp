#include <pch.h>

#include <GameCore.h>

#include <CommandLineArg.h>
#include <FileUtility.h>
#include <shellapi.h>

namespace CoreProject
{
    extern void ExitGame() noexcept;

    using namespace DirectX;

    using Microsoft::WRL::ComPtr;

    GameCore::GameCore(IGameApp& app) noexcept(false)
    {
        m_gameApp = &app;
        m_deviceResources = std::make_shared<DeviceResources>();
        m_deviceResources->RegisterDeviceNotify(this);

        m_timer = std::make_shared<CoreProject::StepTimer>();

        int argc = 0;
        LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
        CommandLineArgs::Initialize(argc, argv);

        FileUtility::SetupRoot(argv);
    }

    // Initialize the Direct3D resources required to run.
    void GameCore::Initialize(HWND window, int width, int height)
    {
        m_deviceResources->SetWindow(window, width, height);

        m_deviceResources->CreateDeviceResources();
        CreateDeviceDependentResources();

        m_deviceResources->CreateWindowSizeDependentResources();
        CreateWindowSizeDependentResources();

        GameInput::GetInstance().Initialize(window);

        // TODO: Change the timer settings if you want something other than the default variable timestep mode.
        // e.g. for 60 FPS fixed timestep update logic, call:
        /*
        m_timer.SetFixedTimeStep(true);
        m_timer.SetTargetElapsedSeconds(1.0 / 60);
        */
    }

    void GameCore::Shutdown()
    {
        m_gameApp->ReleaseDeviceDependentResources();

        GameInput::GetInstance().Shutdown();
        m_deviceResources->Shutdown();
    }

#pragma region Frame Update
    // Executes the basic game loop.
    void GameCore::Tick()
    {
        m_timer->Tick([&]()
            {
                Update(m_timer);
            });

        Render();
    }

    // Updates the world.
    void GameCore::Update(const std::shared_ptr<CoreProject::StepTimer>& stepTimer)
    {
        GameInput::GetInstance().Update(stepTimer);

        // TODO: Add your game logic here.
        m_gameApp->Update(stepTimer);
    }
#pragma endregion

#pragma region Frame Render
    // Draws the scene.
    void GameCore::Render()
    {
        // Don't try to render anything before the first Update.
        if (m_timer->GetFrameCount() == 0)
        {
            return;
        }

        Clear();

        m_deviceResources->PIXBeginEvent(L"Render");
        auto context = m_deviceResources->GetD3DDeviceContext();

        // TODO: Add your rendering code here.
        m_gameApp->RenderScene(context);

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

        context->ClearRenderTargetView(renderTarget, Colors::Black);
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
        m_timer->ResetElapsedTime();

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
        width = 1280;
        height = 720;
    }
#pragma endregion

#pragma region Direct3D Resources
    // These are the resources that depend on the device.
    void GameCore::CreateDeviceDependentResources()
    {
        auto device = m_deviceResources->GetD3DDevice();

        // TODO: Initialize device dependent objects here (independent of window size).
        device;

        m_gameApp->CreateDeviceDependentResources(m_deviceResources);
    }

    // Allocate all memory resources that change on a window SizeChanged event.
    void GameCore::CreateWindowSizeDependentResources()
    {
        // TODO: Initialize windows-size dependent objects here.
        m_gameApp->CreateWindowSizeDependentResources();
    }

    void GameCore::OnDeviceLost()
    {
        // TODO: Add Direct3D resource cleanup here.
        m_gameApp->ReleaseDeviceDependentResources();
    }

    void GameCore::OnDeviceRestored()
    {
        CreateDeviceDependentResources();

        CreateWindowSizeDependentResources();
    }
#pragma endregion
}

namespace CoreProject
{
    std::unique_ptr<GameCore> g_gameCore;

    LPCWSTR g_szAppName = L"GameDR";

    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    int RunApplication(IGameApp& app, const wchar_t* className, HINSTANCE hInstance, int nCmdShow)
    {
//         UNREFERENCED_PARAMETER(hPrevInstance);
//         UNREFERENCED_PARAMETER(lpCmdLine);

        if (!XMVerifyCPUSupport())
            return 1;

        HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
        if (FAILED(hr))
            return 1;

        g_gameCore = std::make_unique<GameCore>(app);

        // Register class and create window
        {
            // Register class
            WNDCLASSEXW wcex = {};
            wcex.cbSize = sizeof(WNDCLASSEXW);
            wcex.style = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc = WndProc;
            wcex.hInstance = hInstance;
            wcex.hIcon = LoadIconW(hInstance, L"IDI_ICON");
            wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
            wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
            wcex.lpszClassName = L"GameDRWindowClass";
            wcex.hIconSm = LoadIconW(wcex.hInstance, L"IDI_ICON");
            if (!RegisterClassExW(&wcex))
                return 1;

            // Create window
            int w, h;
            g_gameCore->GetDefaultSize(w, h);

            RECT rc = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };

            AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

            int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
            int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;

            HWND hwnd = CreateWindowExW(0, L"GameDRWindowClass", g_szAppName, WS_OVERLAPPEDWINDOW,
                //HWND hwnd = CreateWindowExW(WS_EX_TOPMOST, L"GameDRWindowClass", g_szAppName, WS_POPUP,
                xPos, yPos, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
                nullptr);
            // TODO: Change to CreateWindowExW(WS_EX_TOPMOST, L"GameDRWindowClass", g_szAppName, WS_POPUP,
            // to default to fullscreen.

            if (!hwnd)
                return 1;

            ShowWindow(hwnd, SW_SHOWMAXIMIZED);
            //ShowWindow(hwnd, SW_SHOWMAXIMIZED);
             // TODO: Change nCmdShow to SW_SHOWMAXIMIZED to default to fullscreen.

            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(g_gameCore.get()));

            GetClientRect(hwnd, &rc);

            g_gameCore->Initialize(hwnd, rc.right - rc.left, rc.bottom - rc.top);
        }

        // Main message loop
        MSG msg = {};
        while (WM_QUIT != msg.message)
        {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                g_gameCore->Tick();
            }
        }

        g_gameCore->Shutdown();
        g_gameCore.reset();

        CoUninitialize();

        return static_cast<int>(msg.wParam);
    }

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        static bool s_in_sizemove = false;
        static bool s_in_suspend = false;
        static bool s_minimized = false;
        static bool s_fullscreen = false;
        // TODO: Set s_fullscreen to true if defaulting to fullscreen.

        auto gameCore = reinterpret_cast<GameCore*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        switch (message)
        {
        case WM_PAINT:
            if (s_in_sizemove && gameCore)
            {
                gameCore->Tick();
            }
            else
            {
                PAINTSTRUCT ps;
                (void)BeginPaint(hWnd, &ps);
                EndPaint(hWnd, &ps);
            }
            break;

        case WM_MOVE:
            if (gameCore)
            {
                gameCore->OnWindowMoved();
            }
            break;

        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
            {
                if (!s_minimized)
                {
                    s_minimized = true;
                    if (!s_in_suspend && gameCore)
                        gameCore->OnSuspending();
                    s_in_suspend = true;
                }
            }
            else if (s_minimized)
            {
                s_minimized = false;
                if (s_in_suspend && gameCore)
                    gameCore->OnResuming();
                s_in_suspend = false;
            }
            else if (!s_in_sizemove && gameCore)
            {
                gameCore->OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
            }
            break;

        case WM_ENTERSIZEMOVE:
            s_in_sizemove = true;
            break;

        case WM_EXITSIZEMOVE:
            s_in_sizemove = false;
            if (gameCore)
            {
                RECT rc;
                GetClientRect(hWnd, &rc);

                gameCore->OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);
            }
            break;

        case WM_GETMINMAXINFO:
            if (lParam)
            {
                auto info = reinterpret_cast<MINMAXINFO*>(lParam);
                info->ptMinTrackSize.x = 320;
                info->ptMinTrackSize.y = 200;
            }
            break;

        case WM_ACTIVATEAPP:
            if (gameCore)
            {
                if (wParam)
                {
                    gameCore->OnActivated();
                }
                else
                {
                    gameCore->OnDeactivated();
                }
            }
            break;

        case WM_POWERBROADCAST:
            switch (wParam)
            {
            case PBT_APMQUERYSUSPEND:
                if (!s_in_suspend && gameCore)
                    gameCore->OnSuspending();
                s_in_suspend = true;
                return TRUE;

            case PBT_APMRESUMESUSPEND:
                if (!s_minimized)
                {
                    if (s_in_suspend && gameCore)
                        gameCore->OnResuming();
                    s_in_suspend = false;
                }
                return TRUE;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_SYSKEYDOWN:
            if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
            {
                // Implements the classic ALT+ENTER fullscreen toggle
                if (s_fullscreen)
                {
                    SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
                    SetWindowLongPtr(hWnd, GWL_EXSTYLE, 0);

                    int width = 800;
                    int height = 600;
                    if (gameCore)
                        gameCore->GetDefaultSize(width, height);

                    ShowWindow(hWnd, SW_SHOWNORMAL);

                    SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
                }
                else
                {
                    SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP);
                    SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);

                    SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
                }

                s_fullscreen = !s_fullscreen;
            }
            break;

        case WM_MENUCHAR:
            // A menu is active and the user presses a key that does not correspond
            // to any mnemonic or accelerator key. Ignore so we don't produce an error beep.
            return MAKELRESULT(0, MNC_CLOSE);
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
