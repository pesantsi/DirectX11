#include "pch.h"
#include "Block.h"

namespace CoreProject
{
    // Once both shaders are loaded, create the mesh.
    // Load mesh vertices. Each vertex has a position and a color.
    const VertexPositionColor Block::CubeVertices[] =
    {
        {XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
        {XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
        {XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
        {XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
        {XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
        {XMFLOAT3(0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
        {XMFLOAT3(0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
        {XMFLOAT3(0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
    };

    // Each trio of indices represents
    // a triangle to be rendered on the screen.
    // For example: 0,2,1 means that the vertices with indexes
    // 0, 2 and 1 from the vertex buffer compose the 
    // first triangle of this mesh.
    const unsigned short Block::CubeIndices[] =
    {
        0, 2, 1, // -x
        1, 2, 3,

        4, 5, 6, // +x
        5, 7, 6,

        0, 1, 5, // -y
        0, 5, 4,

        2, 6, 7, // +y
        2, 7, 3,

        0, 4, 6, // -z
        0, 6, 2,

        1, 3, 7, // +z
        1, 7, 5,
    };

    Block::Block()
      : m_isActive(true),
        m_blockType(BlockType::BlockType_Default)
    {
    }

    Block::~Block()
    {
    }
}