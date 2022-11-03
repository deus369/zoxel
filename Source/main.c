//! Zoxel Main
#include <stdbool.h>
#include <string.h>
#include <time.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
// =-= FLECS =-=
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
#define FLECS_REST      // for profiler
#define FLECS_MONITOR   // for profiler 2
#include "../Imports/Flecs/flecs.h"
// =-= Modules =-=
#define SDL_IMAGES
#define USE_VERTEX_BUFFERS
// #define WEB_BUILD
// #define DISABLE_TEXTURES
// --- Core ---
#include "Core/Core/Core.c"
#include "Core/App/App.c"
#include "Core/Inputs/Inputs.c"
#include "Core/Timing/Timing.c"
#include "Core/Transforms/Transforms.c"
#include "Core/Rendering/Rendering.c"
#include "Core/Cameras/Cameras.c"
// --- Inner Core ---
#include "InnerCore/Audios/Audios.c"
#include "InnerCore/Textures/Textures.c"
#include "InnerCore/Tiles/Tiles.c"
#include "InnerCore/Voxels/Voxels.c"
#include "InnerCore/Physics/Physics.c"
// --- Outer Core ---
#include "OuterCore/Animations/Animations.c"
#include "OuterCore/UI/UI.c"
#include "OuterCore/Particles/Particles.c"
#include "OuterCore/Particles2D/Particles2D.c"
// --- Gameplay ---
#include "Gameplay/Characters/Characters.c"
// --- Space ---
#include "Space/Players/Players.c"
#include "Space/Realms/Realms.c"

// Settings 
bool running = true;
bool headless = false;
bool profiler = false;
ecs_entity_t localPlayer;
double lastPrinted;
// Forward Declares
void SpawnGameEntities();
void UpdateLoop();
int ProcessArguments(int argc, char* argv[]);
void PollSDLEvents();
void DebugPrinter();
void RenderLoop_ECSFix();

void ImportModules(ecs_world_t *world)
{
    // Core Modules
    ECS_IMPORT(world, Core);
    if (!headless)
    {
        ECS_IMPORT(world, App);
    }
    ECS_IMPORT(world, Inputs);
    ECS_IMPORT(world, Timing);
    ECS_IMPORT(world, Transforms);
    if (!headless)
    {
        ECS_IMPORT(world, Rendering);
    }
    ECS_IMPORT(world, Cameras);
    // Inner Core
    ECS_IMPORT(world, Textures);
    ECS_IMPORT(world, Physics);
    ECS_IMPORT(world, Voxels);
    // Outer Core
    ECS_IMPORT(world, Particles);
    ECS_IMPORT(world, Particles2D);
    // Gameplay
    ECS_IMPORT(world, Characters);
    // Space
    ECS_IMPORT(world, Players);
}

int main(int argc, char* argv[])
{
    int didFail = ProcessArguments(argc, argv);
    if (didFail == EXIT_FAILURE)
    {
        return EXIT_SUCCESS;
    }
    BeginAppECS(argc, argv, profiler);
    // ecs_log_set_level(1);    // use this for module debug
    ImportModules(world);
    SetMultiThreading();
    SpawnGameEntities();
#ifdef __EMSCRIPTEN__
    // emscripten_set_main_loop(UpdateLoop, 60, 1);
    emscripten_set_main_loop(&UpdateLoop, -1, 1);
#else
    while (running)
    {
        UpdateLoop();
    }
#endif
    EndAppECS();
    if (!headless)
    {
        EndAppOpenGL();
        EndAppSDL();
    }
    return 0;
}

//! Main Game Loop
void UpdateLoop()
{
    // App / Input events
    if (!headless)
    {
        PollSDLEvents();
        #ifdef __EMSCRIPTEN__
        if (UpdateWebCanvas())
        {
            return;
        }
        #endif
    }
    // ecs_log_set_level(1);    // use this to debug system pipelines
    //clock_t t = clock();
    ecs_progress(world, 0);
    DebugPrinter();
    //t = clock() - t;
    //double timeTaken = ((double) 1000.0 * t)/CLOCKS_PER_SEC;
    // printf("ECS Time [%fms]\n", timeTaken);
    // Render Loop
    if (!headless)
    {
        RenderLoop_ECSFix();
    }
}

// used globally in render systems
float4x4 mainCameraMatrix;

void RenderLoop_ECSFix()
{
    const FreeRoam *freeRoam = ecs_get(world, mainCamera, FreeRoam);
    mainCameraMatrix = ecs_get(world, mainCamera, ViewMatrix)->value;
    SDL_SetRelativeMouseMode(freeRoam->value);
    //clock_t t = clock();
    //! Run render system on main thread, until Flecs Threading issue is fixed
    //! Locks Main Mouse.
    TextureUpdateMainThread();
    OpenGLClear();
    OpenGLBeginInstancing(mainCameraMatrix);
    ecs_run(world, ecs_id(InstanceRender2DSystem), 0, NULL);
    OpenGLEndInstancing();
    // seperate materials 2D
    ecs_run(world, ecs_id(RenderMaterial2DSystem), 0, NULL);
    // 3D instancing
    OpenGLBeginInstancing3D(mainCameraMatrix);
    ecs_run(world, ecs_id(InstanceRender3DSystem), 0, NULL);
    OpenGLEndInstancing3D();
    UpdateLoopSDL();
    //t = clock() - t;
    //double timeTaken = ((double) 1000.0 * t)/CLOCKS_PER_SEC;
    // printf("Render Time [%fms]\n", timeTaken);
}

void SpawnGameEntities()
{
    SpawnMainCamera(screenDimensions);
    SpawnKeyboardEntity();
    SpawnMouseEntity();
    localPlayer = SpawnPlayerCharacter2D(world);
}

// === Move these to App module ===

void ExitApp()
{
    running = false;
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #endif
}

//! Temporary, quick and dirty events.
void PollSDLEvents()
{
    ResetDevices(world);
    SDL_Event event  = { 0 };
    while (SDL_PollEvent(&event))
    {
        ExtractKeyboard(world, event);
        ExtractMouseEvent(world, event);
        int eventType = event.type;
        if (eventType == SDL_QUIT)
        {
            ExitApp();
        }
        else if (eventType == SDL_KEYUP)
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) 
            {
                ExitApp();
            }
            // test
            else if (key == SDLK_z) 
            {
                const ScreenDimensions *screenDimensions = ecs_get(world, mainCamera, ScreenDimensions);
                const Position *cameraPosition = ecs_get(world, mainCamera, Position);
                const Rotation *cameraRotation = ecs_get(world, mainCamera, Rotation);
                float3 cameraEuler = quaternion_to_euler(cameraRotation->value);
                printf("Le Camera\n");
                printf("    - Dimensions %ix%i\n", screenDimensions->value.x, screenDimensions->value.y);
                printf("    - Position [x:%f y:%f z:%f]\n", cameraPosition->value.x, cameraPosition->value.y, cameraPosition->value.z);
                printf("    - Euler [x:%f y:%f z:%f]\n", cameraEuler.x, cameraEuler.y, cameraEuler.z);
                // printf("Update Player Character Texture.\n");
                // ecs_set(world, localPlayer, GenerateTexture, { 1 });
                // TestDestroyTexture(world);
            }
        }
        else if (eventType == SDL_WINDOWEVENT)
        {
            // printf("SDL_WINDOWEVENT Window Event!");
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                ResizeOpenGLViewport(event.window.data1, event.window.data2);
                ResizeCameras(event.window.data1, event.window.data2);
            }
            else if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                ResizeOpenGLViewport(event.window.data1, event.window.data2);
                ResizeCameras(event.window.data1, event.window.data2);
            }
        }
    }
}

//! Convert Args to Settings.
int ProcessArguments(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            PrintHelpMenu(argv[0]);
            return EXIT_FAILURE;
        }
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fullscreen") == 0)
        {
            fullscreen = true;
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vsync") == 0)
        {
            vsync = true;
        }
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--profiler") == 0)
        {
            profiler = true;
        }
        if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--headless") == 0)
        {
            headless = true;
        }
    }
    return EXIT_SUCCESS;
}

void DebugPrinter()
{
    /*double time = clock() / 1000000.0;
    if (time - lastPrinted >= 3)
    {
        lastPrinted = time;
        const Position2D *position2D = ecs_get(world, localPlayer, Position2D);
        const Velocity2D *velocity2D = ecs_get(world, localPlayer, Velocity2D);
        if (position2D)
        {
            printf("    Player Position2D: [%fx%f] Velocity2D: [%fx%f]\n",
                position2D->value.x, position2D->value.y, velocity2D->value.x, velocity2D->value.y);
        }
        else
        {
            printf("Position2D is null.");
        }
        const Position *cameraPosition = ecs_get(world, mainCamera, Position);
        // const Velocity2D *velocity2D = ecs_get(world, localPlayer, Velocity2D);
        if (cameraPosition)
        {
            printf("    Camera Position: [%fx%fx%f]\n", cameraPosition->value.x, cameraPosition->value.y, cameraPosition->value.z);
        }
        else
        {
            printf("Position2D is null.");
        }
    }*/
}


// #ifdef __EMSCRIPTEN__
//     if (!running)
//     {
//         emscripten_cancel_main_loop();
//     }
// #endif