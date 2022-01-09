#pragma once

#include <Camera.h>
#include <FreeLookCameraController.h>
#include <Content/ShaderStructures.h>
#include <DeviceResources.h>
#include <IGameObject.h>

using namespace CoreProject_API;
using namespace CoreProject;

namespace GameProject
{
    // This sample renderer instantiates a basic rendering pipeline.
    class Sample3DSceneRenderer : IGameObject
    {
    public:
        // Each vertex has a position and a color.
        static const VertexPositionColor CubeVertices[8];

        // Each trio of indices represents
        // a triangle to be rendered on the screen.
        // For example: 0,2,1 means that the vertices with indexes
        // 0, 2 and 1 from the vertex buffer compose the 
        // first triangle of this mesh.
        static const unsigned short CubeIndices[36];

        Sample3DSceneRenderer();

        // This function can be used to initialize application state and will run after essential
        // hardware resources are allocated.  Some state that does not depend on these resources
        // should still be initialized in the constructor such as pointers and flags.
        void CreateDeviceDependentResources(const std::shared_ptr<IDeviceResources>& deviceResources) override;
        void CreateWindowSizeDependentResources() override;
        void ReleaseDeviceDependentResources() override;

        // The update method will be invoked once per frame.  Both state updating and scene
        // rendering should be handled by this method.
        void Update(const std::shared_ptr<IStepTimer>& stepTimer) override;

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
        std::shared_ptr<IDeviceResources> m_deviceResources;

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

