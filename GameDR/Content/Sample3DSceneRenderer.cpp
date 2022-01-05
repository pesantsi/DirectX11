﻿#include <pch.h>

#include <FileUtility.h>
#include <Content/Sample3DSceneRenderer.h>
#include <FreeLookCameraController.h>
#include <Block.h>

using namespace GameProject;

using namespace DirectX;
using namespace Windows::Foundation;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Sample3DSceneRenderer::Sample3DSceneRenderer() :
    m_loadingComplete(false),
    m_degreesPerSecond(45),
    m_indexCount(0),
    m_tracking(false),
    m_deviceResources(nullptr),
    m_constantBufferData(),
    m_CameraController(nullptr),
    m_Camera()
{

}

void Sample3DSceneRenderer::CreateDeviceDependentResources(const std::shared_ptr<CoreProject::DeviceResources>& deviceResources)
{
    m_deviceResources = deviceResources;

    // Load shaders synchronously.
    CoreProject::ByteArray vertexShaderArray = CoreProject::FileUtility::ReadFileSync(L"SampleVertexShader.cso");
    CoreProject::ByteArray pixelShaderArray = CoreProject::FileUtility::ReadFileSync(L"SamplePixelShader.cso");

    FAILED(
        m_deviceResources->GetD3DDevice()->CreateVertexShader(
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
        m_deviceResources->GetD3DDevice()->CreateInputLayout(
            vertexDesc,
            ARRAYSIZE(vertexDesc),
            vertexShaderArray->data(),
            vertexShaderArray->size(),
            &m_inputLayout
        ));

    // After the pixel shader file is loaded, create the shader and constant buffer.
    FAILED(
        m_deviceResources->GetD3DDevice()->CreatePixelShader(
            pixelShaderArray->data(),
            pixelShaderArray->size(),
            nullptr,
            &m_pixelShader
        ));

    CD3D11_BUFFER_DESC constantBufferDesc(sizeof(CoreProject::ConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
    FAILED(
        m_deviceResources->GetD3DDevice()->CreateBuffer(
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
        m_deviceResources->GetD3DDevice()->CreateBuffer(
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
        m_deviceResources->GetD3DDevice()->CreateBuffer(
            &indexBufferDesc,
            &indexBufferData,
            &m_indexBuffer
        )
    );

    // Each vertex is one instance of the VertexPositionColor struct.
    UINT stride = sizeof(CoreProject::VertexPositionColor);
    UINT offset = 0;
    m_deviceResources->GetD3DDeviceContext()->IASetVertexBuffers(
        0,
        1,
        m_vertexBuffer.GetAddressOf(),
        &stride,
        &offset
    );

    m_deviceResources->GetD3DDeviceContext()->IASetIndexBuffer(
        m_indexBuffer.Get(),
        DXGI_FORMAT_R16_UINT, // Each index is one 16-bit unsigned integer (short).
        0
    );

    m_deviceResources->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_deviceResources->GetD3DDeviceContext()->IASetInputLayout(m_inputLayout.Get());

    // Attach our vertex shader.
    m_deviceResources->GetD3DDeviceContext()->VSSetShader(
        m_vertexShader.Get(),
        nullptr,
        0
    );

    // Attach our pixel shader.
    m_deviceResources->GetD3DDeviceContext()->PSSetShader(
        m_pixelShader.Get(),
        nullptr,
        0
    );

    // Once the cube is loaded, the object is ready to be rendered.
    m_loadingComplete = true;
}

// 0-degree Z-rotation
static const XMFLOAT4X4 Rotation0(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

// Initializes view parameters when the window size changes.
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
    RECT outputSize = m_deviceResources->GetOutputSize();
    float aspectRatio = (float)outputSize.right / (float)outputSize.bottom;
    float fovAngleY = 70.0f * XM_PI / 180.0f;

    // This is a simple example of change that can be made when the app is in
    // portrait or snapped view.
    if (aspectRatio < 1.0f)
    {
        fovAngleY *= 2.0f;
    }

    // Note that the OrientationTransform3D matrix is post-multiplied here
    // in order to correctly orient the scene to match the display orientation.
    // This post-multiplication step is required for any draw calls that are
    // made to the swap chain render target. For draw calls to other targets,
    // this transform should not be applied.

    // This sample makes use of a right-handed coordinate system using row-major matrices.
    XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
        fovAngleY,
        aspectRatio,
        0.01f,
        100.0f
    );

    XMFLOAT4X4 orientation = Rotation0;

    XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

    XMStoreFloat4x4(
        &m_constantBufferData.projection,
        XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
    );

    // Eye is at (0,0.7,1.5), looking at point (0,-0.1,0) with the up-vector along the y-axis.
    static const XMVECTORF32 eye = { 0.0f, 0.7f, 1.5f, 0.0f };
    static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };
    static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

    m_Camera.SetEyeAtUp(eye, at, up);
    XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(m_Camera.GetViewMatrix()));

    m_CameraController = std::make_shared<CoreProject::FreeLookCameraController>(m_Camera);

    // XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));

    XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixIdentity());

//     D3D11_RASTERIZER_DESC wfdesc;
//     ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
//     wfdesc.FillMode = D3D11_FILL_WIREFRAME;
//     wfdesc.CullMode = D3D11_CULL_NONE;
//     m_deviceResources->GetD3DDevice()->CreateRasterizerState(&wfdesc, &m_wireFrame);
// 
//     m_deviceResources->GetD3DDeviceContext()->RSSetState(m_wireFrame.Get());
}

// Called once per frame, rotates the cube and calculates the model and view matrices.
void Sample3DSceneRenderer::Update(const std::shared_ptr<CoreProject::StepTimer>& stepTimer)
{ 
    //{
    //    // Convert degrees to radians, then convert seconds to rotation angle
    //    float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
    //    double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
    //    float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

    //    Rotate(radians);
    //}

    m_CameraController->Update(stepTimer);
    XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(m_Camera.GetViewMatrix()));
}

// Rotate the 3D cube model a set amount of radians.
void Sample3DSceneRenderer::Rotate(float radians)
{
    // Prepare to pass the updated model matrix to the shader
    XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
}

void Sample3DSceneRenderer::StartTracking()
{
    m_tracking = true;
}

// When tracking, the 3D cube can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void Sample3DSceneRenderer::TrackingUpdate(float positionX)
{
    if (m_tracking)
    {
        float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().right;
        Rotate(radians);
    }
}

void Sample3DSceneRenderer::StopTracking()
{
    m_tracking = false;
}

// Renders one frame using the vertex and pixel shaders.
void Sample3DSceneRenderer::RenderScene(ID3D11DeviceContext1* deviceContext)
{
    // Loading is asynchronous. Only draw geometry after it's loaded.
    if (!m_loadingComplete)
    {
        return;
    }

    for (float x = 0; x < 32; x++)
    {
        for (float y = 0; y < 32; y++)
        {
            for (float z = 0; z < 32; z++)
            {
                XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixTranslation(x, y, z)));

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
                //pRenderer->TranslateWorldMatrix(x, y, z); // Render m_pBlocks[x][y][z]
            }
        }
    }


}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
    m_loadingComplete = false;
    m_vertexShader.Reset();
    m_inputLayout.Reset();
    m_pixelShader.Reset();
    m_constantBuffer.Reset();
    m_vertexBuffer.Reset();
    m_indexBuffer.Reset();
    m_wireFrame.Reset();
}