#pragma once

#include <Content/Sample3DSceneRenderer.h>
#include <GameCore.h>

namespace GameProject
{
    class GameDR : public CoreProject::IGameApp
    {
    public:

        GameDR();

        void CreateDeviceDependentResources(const std::shared_ptr<CoreProject::DeviceResources>& deviceResources) override;
        void CreateWindowSizeDependentResources() override;
        void ReleaseDeviceDependentResources() override;

        void Update(CoreProject::StepTimer const& timer) override;
        void RenderScene() override;

    private:

        std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;

        //Camera m_Camera;
        //unique_ptr<CameraController> m_CameraController;

        //D3D12_VIEWPORT m_MainViewport;
        //D3D12_RECT m_MainScissor;

        ////ModelInstance m_ModelInst;
        //ShadowCamera m_SunShadowCamera;
    };
}
