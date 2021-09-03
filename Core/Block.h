#pragma once

#include <pch.h>

namespace CoreProject
{

    class Block
    {
    public:
        enum BlockType
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

        Block();
        ~Block();

        bool IsActive();
        void SetActive(bool active);

        void SetBlockType(BlockType BlockType);
        BlockType GetBlockType();

    private:
        bool m_active;
        BlockType m_blockType;
    };
}
