#pragma once

#include <Camera.h>
#include <FreeLookCameraController.h>
#include <Content/ShaderStructures.h>
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
        Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_wireFrame;

        // System resources for cube geometry.
        CoreProject::ConstantBuffer m_constantBufferData;
        uint32_t m_indexCount;

        // Variables used with the rendering loop.
        bool m_loadingComplete;
        float m_degreesPerSecond;
        bool m_tracking;

        CoreProject::Camera m_Camera;
        std::shared_ptr<CoreProject::FreeLookCameraController> m_CameraController;
    };
}

