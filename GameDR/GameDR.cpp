#include <pch.h>

#include <Content/Sample3DSceneRenderer.h>
#include <GameDR.h>
#include <PerlinNoise.h>
#include <PerlinNoiseChunkFactory.h>
#include <PPM.h>

namespace GameProject
{
    GameDR::GameDR()
    {
        m_sceneRenderer = std::unique_ptr<Sample3DSceneRenderer>(new Sample3DSceneRenderer());
        m_chunkFactory = std::make_shared<PerlinNoiseChunkFactory>();
    }

    void GameDR::CreateDeviceDependentResources(const std::shared_ptr<IDeviceResources>& deviceResources)
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

    void GameDR::Update(const std::shared_ptr<IStepTimer>& stepTimer)
    {
        m_sceneRenderer->Update(stepTimer);
    }

    void GameDR::RenderScene(ID3D11DeviceContext1* deviceContext)
    {
        m_sceneRenderer->RenderScene(deviceContext);
    }

    const std::shared_ptr<IWorldChunkFactory>& GameDR::GetWorldChunkFactory()
    {
        return m_chunkFactory;
    }
}

CREATE_APPLICATION(GameProject::GameDR)