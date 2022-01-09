#pragma once

#include <Windows.h>
#include <IGameObject.h>
#include <IWorldChunkFactory.h>

namespace CoreProject_API
{
    interface IGameApp : public IGameObject
    {
    public:
        //World Chunk factory, fetch chunks and sends it to the Chunk Manager to be rendered
        virtual const std::shared_ptr<IWorldChunkFactory>& GetWorldChunkFactory() = 0;

        // Decide if you want the app to exit.  By default, app continues until the 'ESC' key is pressed.
        virtual bool GetIsDone() = 0;
    };
}
