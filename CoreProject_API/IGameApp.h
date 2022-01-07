#pragma once

#include <Windows.h>
#include <IGameObject.h>

namespace CoreProject_API
{
    interface IGameApp : public IGameObject
    {
    public:
        // Decide if you want the app to exit.  By default, app continues until the 'ESC' key is pressed.
        virtual bool IsDone() = 0;
    };
}
