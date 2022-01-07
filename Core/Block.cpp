#include "pch.h"
#include "Block.h"

namespace CoreProject
{
    Block::Block()
      : m_isActive(true),
        m_blockType(BlockType::BlockType_Default)
    {
    }

    Block::~Block()
    {
    }
}