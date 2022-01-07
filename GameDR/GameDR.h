#pragma once

#include <Content/Sample3DSceneRenderer.h>
#include <GameCore.h>
#include <IGameApp.h>

using namespace CoreProject_API;

namespace GameProject
{
    class GameDR : public IGameApp
    {
    public:

        GameDR();

        // This function can be used to initialize application state and will run after essential
        // hardware resources are allocated.  Some state that does not depend on these resources
        // should still be initialized in the constructor such as pointers and flags.
        void CreateDeviceDependentResources(const std::shared_ptr<IDeviceResources>& deviceResources) override;
        void CreateWindowSizeDependentResources() override;
        void ReleaseDeviceDependentResources() override;

        // The update method will be invoked once per frame.  Both state updating and scene
        // rendering should be handled by this method.
        void Update(const std::shared_ptr<IStepTimer>& stepTimer) override;

        // Official rendering pass
        void RenderScene(ID3D11DeviceContext1* deviceContext) override;

        inline bool IsDone() { return false; }
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
