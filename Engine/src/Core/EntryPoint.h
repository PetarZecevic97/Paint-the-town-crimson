#include "precomp.h"
#include "Core/Application.h"
#include "Render/RenderSystem.h"
#include "Render/Renderer.h"

int main(int argc, char* args[])
{
    Engine::Logger::Init();
    LOG_INFO("Logger initialized!");

    auto app = Engine::CreateApplication();
    
    bool success = app->Init();
    if (!success)
    {
        LOG_CRITICAL("Failed to initialize the application!");
        return 1;
    }

    int retval = app->Run();

    success = app->Shutdown();
    if (!success)
    {
        LOG_CRITICAL("Failed to uninitialize the application!");
        return 2;
    }

    delete app;

    return retval;
}
