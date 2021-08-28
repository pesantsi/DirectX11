#pragma once

#include "pch.h"

namespace GameCore
{
    extern bool gIsSupending;

    class IGameApp
    {
    public:
        // This function can be used to initialize application state and will run after essential
        // hardware resources are allocated.  Some state that does not depend on these resources
        // should still be initialized in the constructor such as pointers and flags.
        virtual void Startup() = 0;
        virtual void Cleanup() = 0;

        // Decide if you want the app to exit.  By default, app continues until the 'ESC' key is pressed.
        virtual bool IsDone();

        // The update method will be invoked once per frame.  Both state updating and scene
        // rendering should be handled by this method.
        virtual void Update(float deltaT) = 0;

        // Official rendering pass
        virtual void RenderScene() = 0;

        // Optional UI (overlay) rendering pass.  This is LDR.  The buffer is already cleared.
        virtual void RenderUI(class GraphicsContext&) {};
    };
}
