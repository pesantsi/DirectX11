#include <pch.h>

#include <Chunk.h>
#include <FileUtility.h>

namespace CoreProject
{
    Chunk::Chunk()
    {
    }

    Chunk::~Chunk()
    {
//         // Delete the blocks
//         for (int i = 0; i < CHUNK_SIZE; ++i)
//         {
//             for (int j = 0; j < CHUNK_SIZE; ++j)
//             {
//                 delete[] m_pBlocks[i][j];
//             }
//             delete[] m_pBlocks[i];
//         }
//         delete[] m_pBlocks;
    }

    void Chunk::Load()
    {
//         // Create the blocks
//         m_pBlocks = new Block * *[CHUNK_SIZE];
//         for (int i = 0; i < CHUNK_SIZE; i++)
//         {
//             m_pBlocks[i] = new Block * [CHUNK_SIZE];
//             for (int j = 0; j < CHUNK_SIZE; j++)
//             {
//                 m_pBlocks[i][j] = new Block[CHUNK_SIZE];
//             }
//         }
    }

    void Chunk::Unload()
    {

    }

    void Chunk::Setup()
    {

    }

    void Chunk::RebuildMesh()
    {

    }
}
