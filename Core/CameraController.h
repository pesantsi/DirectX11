#pragma once

#include <pch.h>

#include <Camera.h>
#include <StepTimer.h>
#include <IGameObject.h>

using namespace CoreProject_API;

namespace CoreProject
{
    class CameraController : IUpdatableObject
    {
    public:
        // Assumes worldUp is not the X basis vector
        CameraController(Camera& camera) : m_TargetCamera(camera) {}
        virtual ~CameraController() {}
        virtual void Update(const std::shared_ptr<IStepTimer>& stepTimer) = 0;

    protected:
        Camera& m_TargetCamera;
    };
}
