#ifndef Zoxel_App
#define Zoxel_App
#include <stdbool.h>
//! App Module.

bool vsync = false;
bool fullscreen = false;

#include "SDLUtil.c"

void PrintOpenGL()
{
    // Load the modern OpenGL funcs
    printf("PrintOpenGL: OpenGL\n");
    printf("    Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("    Renderer: %s\n", glGetString(GL_RENDERER));
    printf("    Version:  %s\n", glGetString(GL_VERSION));
    printf("    GLSL Version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void OpenWindow()
{
    int didFail = SetSDLAttributes(vsync);
    PrintSDLDebug();
    if (didFail == EXIT_FAILURE)
    {
        printf("Failed to SetSDLAttributes.");
        return;
    }
    didFail = SpawnWindowSDL(fullscreen);
    PrintOpenGL();
    if (didFail == EXIT_FAILURE)
    {
        printf("Failed to SpawnWindowSDL.");
        return;
    }
}

void AppImport(ecs_world_t *world)
{
    ECS_MODULE(world, App);
    OpenWindow();
}

#endif