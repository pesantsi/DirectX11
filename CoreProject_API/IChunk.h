#pragma once

#include <Windows.h>
#include <IBlock.h>

namespace CoreProject_API
{
    interface IChunk
    {
    public:
        static const unsigned char CHUNK_SIZE = 16;

        virtual bool GetIsLoaded() = 0;
        virtual void Load() = 0;
        virtual void Unload() = 0;

        virtual bool GetIsSetup() = 0;
        virtual void Setup() = 0;

        virtual void RebuildMesh() = 0;

        virtual std::shared_ptr<IBlock> GetBlock(unsigned int x, unsigned int y, unsigned int z) const = 0;
    };
}