#pragma once

#include <pch.h>

#include <StepTimer.h>
#include <Block.h>
#include <IGameObject.h>

namespace CoreProject
{
    class Chunk : CoreProject::IGameObject
    {
    public:
        static const int CHUNK_SIZE = 16;

        Chunk();
        ~Chunk();

        // This function can be used to initialize application state and will run after essential
        // hardware resources are allocated.  Some state that does not depend on these resources
         // should still be initialized in the constructor such as pointers and flags.
        void CreateDeviceDependentResources(const std::shared_ptr<CoreProject::DeviceResources>& deviceResources) override;
        void CreateWindowSizeDependentResources() override;
        void ReleaseDeviceDependentResources() override;

        // The update method will be invoked once per frame.  Both state updating and scene
        // rendering should be handled by this method.
        void Update(const std::shared_ptr<CoreProject::StepTimer>& stepTimer) override;

        // Official rendering pass
        void RenderScene(ID3D11DeviceContext1* deviceContext) override;

    private: // The blocks data
        Block*** m_pBlocks;

        // Direct3D resources for cube geometry.
        Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
        Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

        // System resources for cube geometry.
        CoreProject::ConstantBuffer m_constantBufferData;
        uint32_t m_indexCount;
    };
}
