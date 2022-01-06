#include <pch.h>

#include <Camera.h>

namespace CoreProject
{
    void Camera::SetEyeAtUp(XMVECTOR eyePosition, XMVECTOR focusPosition, XMVECTOR upDirection)
    {
        SetEyePosition(eyePosition);
        SetFocusPosition(focusPosition);
        SetUpDirection(upDirection);

        SetLookDirection(eyePosition, focusPosition, upDirection);
    }

    void Camera::SetLookDirection(XMVECTOR eyePosition, XMVECTOR focusPosition, XMVECTOR upDirection)
    {
        m_viewMatrix = XMMatrixLookAtRH(eyePosition, focusPosition, upDirection);
    }

    void Camera::SetEyePosition(XMVECTOR eyePosition)
    {
        m_eyePosition = eyePosition;
    }

    void Camera::SetFocusPosition(XMVECTOR focusPosition)
    {
        m_focusPosition = focusPosition;
    }

    void Camera::SetUpDirection(XMVECTOR upDirection)
    {
        m_upDirection = upDirection;
    }

    void Camera::Update(StepTimer const&)
    {
    }
}
