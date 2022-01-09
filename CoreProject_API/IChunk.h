#pragma once

#include <Windows.h>
#include <memory>
#include <IBlock.h>

namespace CoreProject_API
{
    interface IChunk
    {
    public:
        static const unsigned char CHUNK_SIZE = 16;

        virtual std::shared_ptr<IBlock> GetBlock(unsigned int x, unsigned int y, unsigned int z) const = 0;
    };
}