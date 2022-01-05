#include <pch.h>

#include <Chunk.h>
#include <FileUtility.h>

namespace CoreProject
{
    Chunk::Chunk() : 
        m_indexCount(0)
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
        // Load shaders synchronously.
        CoreProject::ByteArray vertexShaderArray = CoreProject::FileUtility::ReadFileSync(L"SampleVertexShader.cso");
        CoreProject::ByteArray pixelShaderArray = CoreProject::FileUtility::ReadFileSync(L"SamplePixelShader.cso");

        FAILED(
            deviceResources->GetD3DDevice()->CreateVertexShader(
                vertexShaderArray->data(),
                vertexShaderArray->size(),
                nullptr,
                &m_vertexShader
            ));

        static const D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };

        FAILED(
            deviceResources->GetD3DDevice()->CreateInputLayout(
                vertexDesc,
                ARRAYSIZE(vertexDesc),
                vertexShaderArray->data(),
                vertexShaderArray->size(),
                &m_inputLayout
            ));

        // After the pixel shader file is loaded, create the shader and constant buffer.
        FAILED(
            deviceResources->GetD3DDevice()->CreatePixelShader(
                pixelShaderArray->data(),
                pixelShaderArray->size(),
                nullptr,
                &m_pixelShader
            ));

        CD3D11_BUFFER_DESC constantBufferDesc(sizeof(CoreProject::ConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
        FAILED(
            deviceResources->GetD3DDevice()->CreateBuffer(
                &constantBufferDesc,
                nullptr,
                &m_constantBuffer
            ));

        // Once both shaders are loaded, create the mesh.
        // Load mesh vertices. Each vertex has a position and a color.
        D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
        vertexBufferData.pSysMem = CoreProject::Block::CubeVertices;
        vertexBufferData.SysMemPitch = 0;
        vertexBufferData.SysMemSlicePitch = 0;
        CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(CoreProject::Block::CubeVertices), D3D11_BIND_VERTEX_BUFFER);
        FAILED(
            deviceResources->GetD3DDevice()->CreateBuffer(
                &vertexBufferDesc,
                &vertexBufferData,
                &m_vertexBuffer
            ));

        m_indexCount = ARRAYSIZE(CoreProject::Block::CubeIndices);

        D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
        indexBufferData.pSysMem = CoreProject::Block::CubeIndices;
        indexBufferData.SysMemPitch = 0;
        indexBufferData.SysMemSlicePitch = 0;
        CD3D11_BUFFER_DESC indexBufferDesc(sizeof(CoreProject::Block::CubeIndices), D3D11_BIND_INDEX_BUFFER);
        FAILED(
            deviceResources->GetD3DDevice()->CreateBuffer(
                &indexBufferDesc,
                &indexBufferData,
                &m_indexBuffer
            )
        );

        // Each vertex is one instance of the VertexPositionColor struct.
        UINT stride = sizeof(CoreProject::VertexPositionColor);
        UINT offset = 0;
        deviceResources->GetD3DDeviceContext()->IASetVertexBuffers(
            0,
            1,
            m_vertexBuffer.GetAddressOf(),
            &stride,
            &offset
        );

        deviceResources->GetD3DDeviceContext()->IASetIndexBuffer(
            m_indexBuffer.Get(),
            DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
            0
        );

        deviceResources->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        deviceResources->GetD3DDeviceContext()->IASetInputLayout(m_inputLayout.Get());

        // Attach our vertex shader.
        deviceResources->GetD3DDeviceContext()->VSSetShader(
            m_vertexShader.Get(),
            nullptr,
            0
        );

        // Attach our pixel shader.
        deviceResources->GetD3DDeviceContext()->PSSetShader(
            m_pixelShader.Get(),
            nullptr,
            0
        );
    }

    void Chunk::CreateWindowSizeDependentResources()
    {

    }

    void Chunk::ReleaseDeviceDependentResources()
    {
        m_vertexShader.Reset();
        m_inputLayout.Reset();
        m_pixelShader.Reset();
        m_constantBuffer.Reset();
        m_vertexBuffer.Reset();
        m_indexBuffer.Reset();
    }

    // The update method will be invoked once per frame.  Both state updating and scene
    // rendering should be handled by this method.
    void Chunk::Update(const std::shared_ptr<CoreProject::StepTimer>& stepTimer)
    {

    }

    // Official rendering pass
    void Chunk::RenderScene(ID3D11DeviceContext1* deviceContext)
    {
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                for (int z = 0; z < CHUNK_SIZE; z++)
                {
                    if(!m_pBlocks[x][y][z].GetIsActive())
                        continue;

                    XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixTranslation(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z))));

                    // Prepare the constant buffer to send it to the graphics device.
                    deviceContext->UpdateSubresource1(
                        m_constantBuffer.Get(),
                        0,
                        NULL,
                        &m_constantBufferData,
                        0,
                        0,
                        0
                    );

                    // Send the constant buffer to the graphics device.
                    deviceContext->VSSetConstantBuffers1(
                        0,
                        1,
                        m_constantBuffer.GetAddressOf(),
                        nullptr,
                        nullptr
                    );

                    // Draw the objects.
                    deviceContext->DrawIndexed(
                        m_indexCount,
                        0,
                        0
                    );
                }
            }
        }
    }
}
