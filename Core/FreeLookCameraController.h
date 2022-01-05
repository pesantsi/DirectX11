#pragma once

#include <pch.h>

#include <CameraController.h>

namespace CoreProject
{
    class FreeLookCameraController : CameraController
    {
    public:
        FreeLookCameraController(Camera& camera);
        void Update(const std::shared_ptr<CoreProject::StepTimer>& stepTimer) override;

        void UpdateCamera();
    private:
        float m_moveLeftRight = 1.0f;
        float m_moveBackForward = 1.0f;

        float m_camYaw = 0.0f;
        float m_camPitch = 0.0f;

        XMVECTOR m_defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
        XMVECTOR m_defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

        XMVECTOR m_camPosition = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
        XMVECTOR m_camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
        XMVECTOR m_camUp = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
        XMVECTOR m_camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
        XMVECTOR m_camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

        XMMATRIX m_camRotationMatrix;
    };
}