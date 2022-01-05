#pragma once

#include <IGameObject.h>

namespace CoreProject
{
    class ChuckManager : IUpdatableObject, IRenderableObject
    {
    public:
        // Inherited via IUpdatableObject
        void Update(const std::shared_ptr<CoreProject::StepTimer>& stepTimer) override;

        // Inherited via IRenderableObject
        void RenderScene(ID3D11DeviceContext1* deviceContext) override;

    private:
        void UpdateAsyncChunker();
        void UpdateLoadList();
        void UpdateSetupList();
        void UpdateRebuildList();
        void UpdateFlagsList();
        void UpdateUnloadList();
        void UpdateVisibilityList();
        void UpdateRenderList();
    };
}
