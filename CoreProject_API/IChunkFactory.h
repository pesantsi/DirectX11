#pragma once

#include <Windows.h>
#include <IChunk.h>

namespace CoreProject_API
{
    interface IChunkFactory
    {
    public:
        virtual std::shared_ptr<IChunk> Construct(unsigned int chunkX, unsigned int chunkY, unsigned int chunkZ) = 0;
    };
}