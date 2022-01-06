#pragma once

#include <IGameObject.h>
#include <Chunk.h>

namespace CoreProject
{
    typedef std::vector<std::shared_ptr<Chunk>> ChunkList;

    class ChuckManager : IUpdatableObject, IRenderableObject
    {
    public:
        static const int ASYNC_NUM_CHUNKS_PER_FRAME = 10;

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

        ChunkList m_vpChunkLoadList;
        ChunkList m_vpChunkSetupList;
        ChunkList m_vpChunkRebuildList;
        ChunkList m_vpChunkUpdateFlagsList;
        ChunkList m_vpChunkUnloadList;
        ChunkList m_vpChunkRenderList;
        ChunkList m_vpChunkVisibilityList;

        bool m_forceVisibilityUpdate = false;
    };
}
