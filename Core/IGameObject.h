#pragma once

#include <pch.h>

#include <DeviceResources.h>
#include <StepTimer.h>

namespace CoreProject
{
    interface IDeviceDependentObject
    {
    public:
        // This function can be used to initialize application state and will run after essential
        // hardware resources are allocated.  Some state that does not depend on these resources
        // should still be initialized in the constructor such as pointers and flags.
        virtual void CreateDeviceDependentResources(const std::shared_ptr<CoreProject::DeviceResources>& deviceResources) = 0;
        virtual void CreateWindowSizeDependentResources() = 0;
        virtual void ReleaseDeviceDependentResources() = 0;
    };

    interface IUpdatableObject
    {
    public:
        // The update method will be invoked once per frame. Both state updating and scene
        // rendering should be handled by this method.
        virtual void Update(const std::shared_ptr<CoreProject::StepTimer>& stepTimer) = 0;
    };

    interface IRenderableObject
    {
    public:
        // Official rendering pass
        virtual void RenderScene(ID3D11DeviceContext1* deviceContext) = 0;

        // Optional UI (overlay) rendering pass. This is LDR. The buffer is already cleared.
        virtual void RenderUI(class GraphicsContext&) {};
    };

    interface IGameObject : IDeviceDependentObject, IUpdatableObject, IRenderableObject
    {
    };
}
