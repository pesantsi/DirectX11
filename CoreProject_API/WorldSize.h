#pragma once

#include <IChunk.h>

namespace CoreProject_API
{
    struct WorldSize
    {
        unsigned int blockWide;
        unsigned int blockHigh;
        unsigned int blockDeep;

        WorldSize(unsigned int bWide, unsigned int bDeep, unsigned int bHigh) :
            blockWide(bWide),
            blockDeep(bDeep),
            blockHigh(bHigh)
        {
            if (bWide % IChunk::CHUNK_SIZE > 0 || bHigh % IChunk::CHUNK_SIZE > 0 || bDeep % IChunk::CHUNK_SIZE > 0)
            {
                //throw VoxelEngineException("Width, height and depth must be a multiple of IChunk::Width, IChunk::Height and IChunk::Depth respectively");
            }
        }
    };
}