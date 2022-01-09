#pragma once

#include <IWorldChunkFactory.h>

using namespace CoreProject_API;

namespace PerlinLandscape
{
    class PerlinNoiseChunkFactory : public IWorldChunkFactory
    {
    public:
        PerlinNoiseChunkFactory();

        // Inherited via IWorldChunkFactory
        const WorldSize& GetWorldSize() override;

        // Inherited via IWorldChunkFactory
        std::shared_ptr<IChunk> Construct(unsigned int chunkX, unsigned int chunkY, unsigned int chunkZ) override;

    private:
        WorldSize m_worldSize;
    };
}

