#pragma once

#include <pch.h>

#include <StepTimer.h>

namespace CoreProject
{
    using namespace DirectX;

    class Camera
    {
    public:
        const XMMATRIX& GetViewMatrix() const { return m_viewMatrix; }
        const XMVECTOR& GetEyePosition() const { return m_eyePosition; }
        const XMVECTOR& GetFocusPosition() const { return m_focusPosition; }
        const XMVECTOR& GetUpDirection() const { return m_upDirection; }

        void SetEyeAtUp(XMVECTOR eyePosition, XMVECTOR focusPosition, XMVECTOR upDirection);
        void SetLookDirection(XMVECTOR eyePosition, XMVECTOR focusPosition, XMVECTOR upDirection);
        void SetEyePosition(XMVECTOR eyePosition);
        void SetFocusPosition(XMVECTOR focusPosition);
        void SetUpDirection(XMVECTOR upDirection);

        void Update(StepTimer const& timer);

    private:
        XMMATRIX m_viewMatrix;
        XMVECTOR m_eyePosition;
        XMVECTOR m_focusPosition;
        XMVECTOR m_upDirection;
    };
}