#include <pch.h>

#include <FreeLookCameraController.h>
#include <GameInput.h>

namespace CoreProject
{
    FreeLookCameraController::FreeLookCameraController(Camera& camera)
        : CameraController(camera)
        , m_camRotationMatrix()
    {
        m_camPosition = camera.GetEyePosition();
        m_camTarget = camera.GetFocusPosition();
        m_camUp = camera.GetUpDirection();
    }

    void FreeLookCameraController::Update(const std::shared_ptr<IStepTimer>& stepTimer)
    {
        float speed = 5.0f * (float)stepTimer->GetElapsedSeconds();

        if (GameInput::GetInstance().IsPressed(GameInput::DigitalInput::kKey_a))
        {
            m_moveLeftRight += speed;
        }

        if (GameInput::GetInstance().IsPressed(GameInput::DigitalInput::kKey_d))
        {
            m_moveLeftRight -= speed;
        }

        if (GameInput::GetInstance().IsPressed(GameInput::DigitalInput::kKey_w))
        {
            m_moveBackForward += speed;
        }

        if (GameInput::GetInstance().IsPressed(GameInput::DigitalInput::kKey_s))
        {
            m_moveBackForward -= speed;
        }

        m_camYaw += GameInput::GetInstance().GetAnalogInput(GameInput::kAnalogMouseX) * 0.50f;
        m_camPitch += GameInput::GetInstance().GetAnalogInput(GameInput::kAnalogMouseY) * 0.50f;

        UpdateCamera();
    }

    void FreeLookCameraController::UpdateCamera()
    {
        m_camRotationMatrix = XMMatrixRotationRollPitchYaw(m_camPitch, m_camYaw, 0);
        m_camTarget = XMVector3TransformCoord(m_defaultForward, m_camRotationMatrix);
        m_camTarget = XMVector3Normalize(m_camTarget);

        // Free-Look Camera
        m_camRight = XMVector3TransformCoord(m_defaultRight, m_camRotationMatrix);
        m_camForward = XMVector3TransformCoord(m_defaultForward, m_camRotationMatrix);
        m_camUp = XMVector3Cross(m_camForward, m_camRight);

        m_camPosition += m_moveLeftRight * m_camRight;
        m_camPosition += m_moveBackForward * m_camForward;

        m_moveLeftRight = 0.0f;
        m_moveBackForward = 0.0f;

        m_camTarget = m_camPosition + m_camTarget;

        m_TargetCamera.SetEyeAtUp(m_camPosition, m_camTarget, m_camUp);
    }
}
