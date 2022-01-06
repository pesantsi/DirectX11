#pragma once

#include <pch.h>

#include <Content/ShaderStructures.h>

namespace CoreProject
{
    class Block
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

        // Each vertex has a position and a color.
        static const VertexPositionColor CubeVertices[8];

        // Each trio of indices represents
        // a triangle to be rendered on the screen.
        // For example: 0,2,1 means that the vertices with indexes
        // 0, 2 and 1 from the vertex buffer compose the 
        // first triangle of this mesh.
        static const unsigned short CubeIndices[36];

        static const unsigned short BLOCK_RENDER_SIZE = 1;

        Block();
        ~Block();

        inline bool GetIsActive() { return m_isActive; }
        inline void SetIsActive(bool isActive) { m_isActive = isActive; }

        inline BlockType GetBlockType() { return m_blockType; }
        inline void SetBlockType(BlockType blockType) { m_blockType = blockType; }

    private:
        bool m_isActive;
        BlockType m_blockType;
    };
}
