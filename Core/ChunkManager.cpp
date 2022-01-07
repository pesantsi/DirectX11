#include "pch.h"
#include "ChunkManager.h"

namespace CoreProject
{
    void ChunkManager::Update(const std::shared_ptr<IStepTimer >&)
    {
        UpdateAsyncChunker();
        UpdateLoadList();
        UpdateSetupList();
        UpdateRebuildList();
        UpdateFlagsList();
        UpdateUnloadList();
//         UpdateVisibilityList(cameraPosition);
//         if (m_cameraPosition != cameraPosition || m_cameraView != cameraView) {
//             UpdateRenderList();
//         }
//         m_cameraPosition = cameraPosition;
//         m_cameraView = cameraView;
    }

    void ChunkManager::RenderScene(ID3D11DeviceContext1*)
    {
    }

    void ChunkManager::UpdateAsyncChunker()
    {
    }

    void ChunkManager::UpdateLoadList()
    {
        int lNumOfChunksLoaded = 0;
        ChunkList::iterator iterator;
        for (iterator = m_vpChunkLoadList.begin(); iterator != m_vpChunkLoadList.end() && (lNumOfChunksLoaded != ASYNC_NUM_CHUNKS_PER_FRAME); ++iterator)
        {
            std::shared_ptr<Chunk> pChunk = (*iterator);
            if (pChunk->GetIsLoaded() == false)
            {
                if (lNumOfChunksLoaded != ASYNC_NUM_CHUNKS_PER_FRAME)
                {
                    pChunk->Load();
                    
                    // Increase the chunks loaded count
                    lNumOfChunksLoaded++;
                    m_forceVisibilityUpdate = true;
                }
            }
        }
        // Clear the load list (every frame)     
        m_vpChunkLoadList.clear();
    }

    void ChunkManager::UpdateSetupList()
    {
        ChunkList::iterator iterator;
        for (iterator = m_vpChunkSetupList.begin(); iterator != m_vpChunkSetupList.end(); ++iterator)
        {
            std::shared_ptr<Chunk> pChunk = (*iterator);
            if (pChunk->GetIsLoaded() && pChunk->GetIsSetup() == false)
            {
                pChunk->Setup();
                if (pChunk->GetIsSetup())
                {
                    // Only force the visibility update if we actually setup the chunk, some chunks wait in the pre-setup stage... 
                    m_forceVisibilityUpdate = true;
                }
            }
        }
        // Clear the setup list (every frame)    
        m_vpChunkSetupList.clear();
    }

    void ChunkManager::UpdateRebuildList()
    {
        // Rebuild any chunks that are in the rebuild chunk list     
        ChunkList::iterator iterator;
        int lNumRebuiltChunkThisFrame = 0;
        for (iterator = m_vpChunkRebuildList.begin(); iterator != m_vpChunkRebuildList.end() && (lNumRebuiltChunkThisFrame != ASYNC_NUM_CHUNKS_PER_FRAME); ++iterator)
        {
            std::shared_ptr<Chunk> pChunk = (*iterator);
            if (pChunk->GetIsLoaded() && pChunk->GetIsSetup())
            {
                if (lNumRebuiltChunkThisFrame != ASYNC_NUM_CHUNKS_PER_FRAME)
                {
                    pChunk->RebuildMesh();

                    // If we rebuild a chunk, add it to the list of chunks that need their render flags updated since we might now be empty or surrounded
                    m_vpChunkUpdateFlagsList.push_back(pChunk);
                    
//                     // Also add our neighbors since they might now be surrounded too (If we have neighbors)
//                     Chunk* pChunkXMinus = GetChunk(pChunk->GetX() - 1, pChunk->GetY(), pChunk->GetZ());
//                     Chunk* pChunkXPlus = GetChunk(pChunk->GetX() + 1, pChunk->GetY(), pChunk->GetZ());
//                     Chunk* pChunkYMinus = GetChunk(pChunk->GetX(), pChunk->GetY() - 1, pChunk->GetZ());
//                     Chunk* pChunkYPlus = GetChunk(pChunk->GetX(), pChunk->GetY() + 1, pChunk->GetZ());
//                     Chunk* pChunkZMinus = GetChunk(pChunk->GetX(), pChunk->GetY(), pChunk->GetZ() - 1);
//                     Chunk* pChunkZPlus = GetChunk(pChunk->GetX(), pChunk->GetY(), pChunk->GetZ() + 1);
// 
//                     if (pChunkXMinus != NULL) 
//                         m_vpChunkUpdateFlagsList.push_back(pChunkXMinus);
//                     if (pChunkXPlus != NULL)
//                         m_vpChunkUpdateFlagsList.push_back(pChunkXPlus);
//                     if (pChunkYMinus != NULL)
//                         m_vpChunkUpdateFlagsList.push_back(pChunkYMinus);
//                     if (pChunkYPlus != NULL)
//                         m_vpChunkUpdateFlagsList.push_back(pChunkYPlus);
//                     if (pChunkZMinus != NULL)
//                         m_vpChunkUpdateFlagsList.push_back(pChunkZMinus);
//                     if (pChunkZPlus != NULL)
//                         m_vpChunkUpdateFlagsList.push_back(pChunkZPlus); 
                    
                    // Only rebuild a certain number of chunks per frame   
                    lNumRebuiltChunkThisFrame++;
                    m_forceVisibilityUpdate = true;
                }
            }
        }
        // Clear the rebuild list     
        m_vpChunkRebuildList.clear();
    }

    void ChunkManager::UpdateFlagsList()
    {
    }

    void ChunkManager::UpdateUnloadList()
    {
        ChunkList::iterator iterator;
        for (iterator = m_vpChunkUnloadList.begin(); iterator != m_vpChunkUnloadList.end(); ++iterator)
        {
            std::shared_ptr<Chunk> pChunk = (*iterator);
            if (pChunk->GetIsLoaded())
            {
                pChunk->Unload();
                m_forceVisibilityUpdate = true;
            }
        }
        // Clear the unload list (every frame)    
        m_vpChunkUnloadList.clear();
    }

    void ChunkManager::UpdateVisibilityList()
    {
    }

    void ChunkManager::UpdateRenderList()
    {
        // Clear the render list each frame BEFORE we do our tests to see what chunks should be rendered     
        m_vpChunkRenderList.clear();
        ChunkList::iterator iterator;
        for (iterator = m_vpChunkVisibilityList.begin(); iterator != m_vpChunkVisibilityList.end(); ++iterator)
        {
            std::shared_ptr<Chunk> pChunk = (*iterator);
            if (pChunk != NULL)
            {
                if (pChunk->GetIsLoaded() && pChunk->GetIsSetup())
                {
//                     if (pChunk->ShouldRender()) // Early flags check so we don't always have to do the frustum check... 
//                     {
//                         // Check if this chunk is inside the camera frustum                    
//                         float c_offset = (Chunk::CHUNK_SIZE * Block::BLOCK_RENDER_SIZE) - Block::BLOCK_RENDER_SIZE;
//                         Vector3d chunkCenter = pChunk->GetPosition() + Vector3d(c_offset, c_offset, c_offset);
//                         float c_size = Chunk::CHUNK_SIZE * Block::BLOCK_RENDER_SIZE;
//                         if (m_pRenderer->CubeInFrustum(m_pRenderer->GetActiveViewPort(), chunkCenter, c_size, c_size, c_size))
//                         {
//                             m_vpChunkRenderList.push_back(pChunk);
//                         }
//                     }
                }
            }
        }
    }
}
