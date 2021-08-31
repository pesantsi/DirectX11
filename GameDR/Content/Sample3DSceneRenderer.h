#pragma once

#include <Content\ShaderStructures.h>
#include <DeviceResources.h>
#include <IGameObject.h>
#include <StepTimer.h>

namespace GameProject
{
    // This sample renderer instantiates a basic rendering pipeline.
    class Sample3DSceneRenderer : CoreProject::IGameObject
    {
    public:
        Sample3DSceneRenderer();
        void CreateDeviceDependentResources(const std::shared_ptr<CoreProject::DeviceResources>& deviceResources) override;
        void CreateWindowSizeDependentResources() override;
        void ReleaseDeviceDependentResources() override;
        void Update(CoreProject::StepTimer const& timer) override;
        void RenderScene() override;
        void StartTracking();
        void TrackingUpdate(float positionX);
        void StopTracking();
        bool IsTracking() { return m_tracking; }


    private:
        void Rotate(float radians);

    private:
        // Cached pointer to device resources.
        std::shared_ptr<CoreProject::DeviceResources> m_deviceResources;

        // Direct3D resources for cube geometry.
        Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
        Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

        // System resources for cube geometry.
        ConstantBuffer m_constantBufferData;
        uint32_t m_indexCount;

        // Variables used with the rendering loop.
        bool m_loadingComplete;
        float m_degreesPerSecond;
        bool m_tracking;
    };
}

