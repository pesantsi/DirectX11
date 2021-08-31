 #include "pch.h"

#include "GameDR.h"

#include "Content/Sample3DSceneRenderer.h"

namespace GameProject
{
    GameDR::GameDR()
    {
        m_sceneRenderer = std::unique_ptr<Sample3DSceneRenderer>(new Sample3DSceneRenderer());
    }

    void GameDR::CreateDeviceDependentResources(const std::shared_ptr<CoreProject::DeviceResources>& deviceResources)
    {
        m_sceneRenderer->CreateDeviceDependentResources(deviceResources);
    }

    void GameDR::CreateWindowSizeDependentResources()
    {
        m_sceneRenderer->CreateWindowSizeDependentResources();
    }

    void GameDR::ReleaseDeviceDependentResources()
    {
        m_sceneRenderer->ReleaseDeviceDependentResources();
    }

    void GameDR::Update(CoreProject::StepTimer const& timer)
    {
        m_sceneRenderer->Update(timer);
    }

    void GameDR::RenderScene()
    {
        m_sceneRenderer->RenderScene();
    }
}

CREATE_APPLICATION(GameProject::GameDR)