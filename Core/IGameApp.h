#pragma once

#include <pch.h>

#include <DeviceResources.h>
#include <StepTimer.h>
#include <IGameObject.h>

namespace CoreProject
{
    extern bool gIsSupending;

    interface IGameApp : IGameObject
    {
    public:
        // Decide if you want the app to exit.  By default, app continues until the 'ESC' key is pressed.
        virtual bool IsDone() { return false; }
    };
}
