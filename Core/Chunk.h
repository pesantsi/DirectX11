#pragma once

#include <pch.h>

#include <Block.h>
#include <IChunk.h>

using namespace CoreProject_API;

namespace CoreProject
{
    class Chunk : public IChunk
    {
    public:

        Chunk();
        ~Chunk();

        inline bool GetIsLoaded() { return m_isLoaded; }
        void Load();
        void Unload();

        inline bool GetIsSetup() { return m_isSetup; }
        void Setup();

        void RebuildMesh();

    private:

        static unsigned int GetBlockIndex(unsigned int x, unsigned int y, unsigned int z) { return z * IChunk::CHUNK_SIZE * IChunk::CHUNK_SIZE + y * IChunk::CHUNK_SIZE + x; }

        bool m_isLoaded = false;
        bool m_isSetup = false;

        // The blocks data
        std::vector<std::shared_ptr<Block>> m_pBlocks;
    };
}
