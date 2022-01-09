#include "PerlinNoiseChunkFactory.h"

namespace PerlinLandscape
{
    PerlinNoiseChunkFactory::PerlinNoiseChunkFactory() :
        m_worldSize(0,0,0)
    {
        m_worldSize.blockDeep = 1024;
        m_worldSize.blockWide = 1024;
        m_worldSize.blockHigh = 256;

        // 
// 
//         // Define the size of the image
//         unsigned int width = 1024, height = 1024;
// 
//         // Create an empty PPM image
//         PerlinLandscape::PPM image(width, height);
// 
//         // Create a PerlinNoise object with a random permutation vector generated with seed
//         unsigned int seed = 237;
//         PerlinLandscape::PerlinNoise pn(seed);
// 
//         unsigned int kk = 0;
//         // Visit every pixel of the image and assign a color generated with Perlin noise
//         for (unsigned int i = 0; i < height; ++i) {     // y
//             for (unsigned int j = 0; j < width; ++j) {  // x
//                 double x = (double)j / ((double)width);
//                 double y = (double)i / ((double)height);
// 
//                 // Typical Perlin noise
//                 double n = pn.Noise(10 * x, 10 * y, 0.8);
// 
//                 // Wood like structure
//                 //n = 20 * pn.noise(x, y, 0.8);
//                 //n = n - floor(n);
// 
//                 // Map the values to the [0, 255] interval, for simplicity we use 
//                 // tones of grey
//                 image.m_r[kk] = static_cast<unsigned char>(floor(255.0f * n));
//                 image.m_g[kk] = static_cast<unsigned char>(floor(255.0f * n));
//                 image.m_b[kk] = static_cast<unsigned char>(floor(255.0f * n));
//                 kk++;
//             }
//         }
// 
//         // Save the image in a binary PPM file
//         image.Write("figure_7_P.ppm");
    }

    const WorldSize& PerlinNoiseChunkFactory::GetWorldSize()
    {
        return m_worldSize;
    }

    std::shared_ptr<IChunk> PerlinNoiseChunkFactory::Construct(unsigned int /*chunkX*/, unsigned int /*chunkY*/, unsigned int /*chunkZ*/)
    {
        return std::shared_ptr<IChunk>();
    }
}
