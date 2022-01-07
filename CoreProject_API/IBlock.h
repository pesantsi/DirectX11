#pragma once

#include <Windows.h>

namespace CoreProject_API
{
    interface IBlock
    {
    public:
        enum class BlockType : int
        {
            BlockType_Default = 0,
            BlockType_Grass,
            BlockType_Dirt,
            BlockType_Water,
            BlockType_Stone,
            BlockType_Wood,
            BlockType_Sand,
            BlockType_NumTypes,
        };

        static const unsigned char BLOCK_RENDER_SIZE = 1;

        virtual bool GetIsActive() = 0;
        virtual BlockType GetBlockType() = 0;
    };
}