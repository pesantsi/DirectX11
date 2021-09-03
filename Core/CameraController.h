#pragma once

#include <pch.h>

#include <Camera.h>
#include <StepTimer.h>

namespace CoreProject
{
    class CameraController
    {
    public:
        // Assumes worldUp is not the X basis vector
        CameraController(Camera& camera) : m_TargetCamera(camera) {}
        virtual ~CameraController() {}
        virtual void Update(StepTimer const& timer) = 0;

    protected:
        Camera& m_TargetCamera;
    };
}
