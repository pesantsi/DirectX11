#pragma once

#include <pch.h>

#include <DeviceResources.h>
#include <StepTimer.h>

namespace CoreProject
{
    extern bool gIsSupending;

    interface IGameObject
    {
    public:
        // This function can be used to initialize application state and will run after essential
        // hardware resources are allocated.  Some state that does not depend on these resources
        // should still be initialized in the constructor such as pointers and flags.
        virtual void CreateDeviceDependentResources(const std::shared_ptr<CoreProject::DeviceResources>& deviceResources) = 0;
        virtual void CreateWindowSizeDependentResources() = 0;
        virtual void ReleaseDeviceDependentResources() = 0;

        // The update method will be invoked once per frame.  Both state updating and scene
        // rendering should be handled by this method.
        virtual void Update(CoreProject::StepTimer const& timer) = 0;

        // Official rendering pass
        virtual void RenderScene() = 0;

        // Optional UI (overlay) rendering pass.  This is LDR.  The buffer is already cleared.
        virtual void RenderUI(class GraphicsContext&) {};
    };
}
