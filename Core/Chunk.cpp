#include <pch.h>

#include <Chunk.h>

namespace CoreProject
{
	Chunk::Chunk() 
	{
		// Create the blocks
		m_pBlocks = new Block * *[CHUNK_SIZE];
		for (int i = 0; i < CHUNK_SIZE; i++) 
		{
			m_pBlocks[i] = new Block * [CHUNK_SIZE];
			for (int j = 0; j < CHUNK_SIZE; j++) 
			{
				m_pBlocks[i][j] = new Block[CHUNK_SIZE];
			}
		}
	}

	Chunk::~Chunk() 
	{ 
		// Delete the blocks
		for (int i = 0; i < CHUNK_SIZE; ++i) 
		{
			for (int j = 0; j < CHUNK_SIZE; ++j) 
			{
				delete[] m_pBlocks[i][j];
			}
			delete[] m_pBlocks[i];
		}
		delete[] m_pBlocks;
	}

	// This function can be used to initialize application state and will run after essential
	// hardware resources are allocated.  Some state that does not depend on these resources
	// should still be initialized in the constructor such as pointers and flags.
	void Chunk::CreateDeviceDependentResources(const std::shared_ptr<CoreProject::DeviceResources>& deviceResources)
	{

	}

	void Chunk::CreateWindowSizeDependentResources()
	{

	}

	void Chunk::ReleaseDeviceDependentResources()
	{

	}

	// The update method will be invoked once per frame.  Both state updating and scene
	// rendering should be handled by this method.
	void Chunk::Update(CoreProject::StepTimer const& timer)
	{

	}

	// Official rendering pass
	void Chunk::RenderScene()
	{

	}
}
