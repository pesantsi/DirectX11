#pragma once

#include <pch.h>

#include <DeviceResources.h>
#include <StepTimer.h>
#include <imgui.h>
#include <windows.h>

namespace CoreProject
{
    class GameImGui
    {
    public:
        static GameImGui& GetInstance()
        {
            // Guaranteed to be destroyed.
             // Instantiated on first use.
            static GameImGui instance;
            return instance;
        }

        GameImGui(GameImGui const&) = delete;
        void operator=(GameImGui const&) = delete;

        void Initialize(HWND window, const std::shared_ptr<CoreProject::DeviceResources>& deviceResources);
        void Update(const std::shared_ptr<CoreProject::StepTimer>& stepTimer);
        void Render();
        void Shutdown();

        LRESULT WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        GameImGui() {}

        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };
}

