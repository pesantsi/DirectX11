#pragma once

#include <Windows.h>
#include <IChunk.h>
#include <WorldSize.h>

namespace CoreProject_API
{
    interface IWorldChunkFactory
    {
    public:
        virtual const WorldSize& GetWorldSize() = 0;

        virtual std::shared_ptr<IChunk> Construct(unsigned int chunkX, unsigned int chunkY, unsigned int chunkZ) = 0;
    };
}