#include <pch.h>

#include <Content/Sample3DSceneRenderer.h>
#include <GameDR.h>

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

    void GameDR::Update(const std::shared_ptr<CoreProject::StepTimer>& stepTimer)
    {
        m_sceneRenderer->Update(stepTimer);
    }

    void GameDR::RenderScene(ID3D11DeviceContext1* deviceContext)
    {
        m_sceneRenderer->RenderScene(deviceContext);
    }
}

CREATE_APPLICATION(GameProject::GameDR)