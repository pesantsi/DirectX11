#pragma once

#include <Content/Sample3DSceneRenderer.h>
#include <GameCore.h>
#include <IGameApp.h>
#include <PerlinNoiseChunkFactory.h>

using namespace CoreProject_API;
using namespace PerlinLandscape;

namespace GameProject
{
    class GameDR : public IGameApp
    {
    public:

        GameDR();

        inline bool GetIsDone() { return false; }

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

        // Inherited via IGameApp
        const std::shared_ptr<IWorldChunkFactory>& GetWorldChunkFactory() override;
    private:

        std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
        std::shared_ptr<IWorldChunkFactory> m_chunkFactory;
    };
}
