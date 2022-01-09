#pragma once

#include <IGameObject.h>
#include <Chunk.h>
#include <IWorldChunkFactory.h>

using namespace CoreProject_API;

namespace CoreProject
{
    //typedef std::unordered_map<int, std::shared_ptr<Chunk>> ChunkList;
    typedef std::vector<std::shared_ptr<Chunk>> ChunkList;

    class ChunkManager : public IUpdatableObject, public IRenderableObject
    {
    public:
        static const int ASYNC_NUM_CHUNKS_PER_FRAME = 10;

        ChunkManager(const std::shared_ptr<IWorldChunkFactory>& worldChunkFactory);

        void Update(const std::shared_ptr<IStepTimer>& stepTimer) override;
        void RenderScene(ID3D11DeviceContext1*) override;

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

        std::shared_ptr<IWorldChunkFactory> m_worldChunkFactory;
    };
}
