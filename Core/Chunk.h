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
        void Load() override;
        void Unload() override;

        inline bool GetIsSetup() { return m_isSetup; }
        void Setup() override;

        void RebuildMesh() override;

    private:
        bool m_isLoaded = false;
        bool m_isSetup = false;

        // The blocks data
        Block*** m_pBlocks;
    };
}
