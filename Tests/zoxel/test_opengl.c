// Test with
//  cc -std=c99 -o test_opengl Source/Imports/Flecs/flecs.c Tests/zoxel/test_opengl.c -lGL -lSDL2 -lSDL2_image -lm -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE
// Run with
//  ./test_opengl
// Add defines first
#define USE_VERTEX_BUFFERS
#include <stdbool.h>
#include <string.h>
// #define SDL_IMAGES
// =-= FLECS =-=
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
#include "../../Source/Imports/Flecs/flecs.h"
#include "../../Source/Imports/Flecs/FlecsUtil.c"
#include "../../Source/Core/Core/Core.c"
#include "../../Source/Core/App/App.c"
#include "../../Source/Core/Transforms2D/Transforms2D.c"
#include "../../Source/Core/Transforms/Transforms.c"
#include "../../Source/Core/Rendering/Rendering.c"
#include "../../Source/Core/Cameras/Cameras.c"

int main(int argc, char* argv[])
{
    SpawnWorld(argc, argv, false, true, 4);
    ECS_IMPORT(world, App);
    ECS_IMPORT(world, Transforms2D);
    ECS_IMPORT(world, Transforms);
    ECS_IMPORT(world, Cameras);
    ECS_IMPORT(world, Rendering);
    SpawnMainCamera(screenDimensions);
    // SpawnKeyboardEntity();
    // SpawnPlayerCharacter2D(world);
    // while true, run main loop here
    bool running = true;
    while (running)
    {
        ecs_progress(world, 0);
        UpdateBeginOpenGL(GetMainCameraViewMatrix());
        ecs_run(world, ecs_id(Render2DSystem), 0, NULL);
        UpdateEndOpenGL();
        UpdateLoopSDL();
    }
    EndECS();
    EndAppGraphics();
    EndSDL();
    return 0;
}