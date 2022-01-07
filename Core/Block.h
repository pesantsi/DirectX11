#pragma once

#include <pch.h>

#include <IBlock.h>

using namespace CoreProject_API;

namespace CoreProject
{
    class Block : IBlock
    {
    public:
        Block();
        ~Block();

        inline bool GetIsActive() override { return m_isActive; }
        inline BlockType GetBlockType() override { return m_blockType; }

    private:
        bool m_isActive;
        BlockType m_blockType;
    };
}
