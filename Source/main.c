// Add defines first
#include <stdbool.h>
#include <string.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#define SDL_IMAGES
#define USE_VERTEX_BUFFERS
// =-= FLECS =-=
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE
#define FLECS_SYSTEM 
#define FLECS_PIPELINE
#include "Imports/Flecs/flecs.h"
#include "Imports/Flecs/FlecsUtil.c"
// =-= Modules =-=
// --- Core Core ---
#include "Core/Core/Core.c"
// --- Core ---
#include "Core/App/App.c"
#include "Core/Timing/Timing.c"
#include "Core/Inputs/Inputs.c"
#include "Core/Transforms2D/Transforms2D.c"
#include "Core/Transforms/Transforms.c"
#include "Core/Physics2D/Physics2D.c"
#include "Core/Physics/Physics.c"
#include "Core/Rendering/Rendering.c"
#include "Core/Cameras/Cameras.c"
#include "Core/Textures/Textures.c"
#include "Core/Voxels/Voxels.c"
// --- Gameplay ---
#include "Gameplay/Particles2D/Particles2D.c"
#include "Gameplay/Characters2D/Characters2D.c"   // for now until i move stuff to characters
// --- Space ---
#include "Space/Players/Players.c"   // for now until i move stuff to characters


#include <sys/sysinfo.h>

// Settings 
const bool isSpawnGameEntities = true;
// Settings  2
bool running = true;
bool headless = false;
bool profiler = false;
ecs_entity_t localPlayer;
double lastPrinted;

// Forward  Declares
int ProcessArguments(int argc, char* argv[]);
void PollSDLEvents();

void ImportModules(ecs_world_t *world)
{
    // Core Modules
    ECS_IMPORT(world, Timing);
    ECS_IMPORT(world, Inputs);
    ECS_IMPORT(world, Transforms2D);
    ECS_IMPORT(world, Transforms);
    if (!headless)
    {
        ECS_IMPORT(world, App);
        ECS_IMPORT(world, Rendering);
    }
    ECS_IMPORT(world, Cameras);
    ECS_IMPORT(world, Textures);
    ECS_IMPORT(world, Voxels);
    ECS_IMPORT(world, Physics2D);
    ECS_IMPORT(world, Physics);
    // Gameplay Modules
    ECS_IMPORT(world, Particles2D);
    ECS_IMPORT(world, Characters2D);
    // Space Modules
    ECS_IMPORT(world, Players);
}

void DebugPlayer()
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
    }*/
}

void UpdateLoop()
{
    // App / Input events
    if (!headless)
    {
        PollSDLEvents();
    }
    ecs_progress(world, 0);
    // Render Loop
    if (!headless)
    {
        UpdateBeginOpenGL(GetMainCameraViewMatrix());
        ecs_run(world, ecs_id(Render2DSystem), 0, NULL);
        UpdateEndOpenGL();
        UpdateLoopSDL();
    }
    // DebugPlayer();
// #ifdef __EMSCRIPTEN__
//     if (!running)
//     {
//         emscripten_cancel_main_loop();
//     }
// #endif
}

void SpawnGameEntities()
{
    SpawnMainCamera(screenDimensions);
    SpawnKeyboardEntity();
    localPlayer = SpawnPlayerCharacter2D(world);
}

int main(int argc, char* argv[])
{
    int didFail = ProcessArguments(argc, argv);
    if (didFail == EXIT_FAILURE)
    {
        return EXIT_SUCCESS;
    }
    SpawnWorld(argc, argv, profiler);
    ImportModules(world);
    int cpuCoreCount = get_nprocs();
    int sdlCoreCount = SDL_GetCPUCount();
    printf("This system has %d processors configured and "
            "%d processors available. SDL Counts %i however.\n",
            get_nprocs_conf(), cpuCoreCount, sdlCoreCount);
    SetMultiThreading(cpuCoreCount);
    if (isSpawnGameEntities)
    {
        SpawnGameEntities();
    }
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(UpdateLoop, 60, 1);
#else
    while (running)
    {
        UpdateLoop();
    }
#endif
    EndECS();
    if (!headless)
    {
        EndAppGraphics();
        EndSDL();
    }
    printf("Ending Zoxel.\n");
    return 0;
}

//! Temporary, quick and dirty events.
void PollSDLEvents()
{
    ResetKeyboard(world);
    SDL_Event event  = { 0 };
    while (SDL_PollEvent(&event))
    {
        ExtractIntoKeyboard(world, event);
        int eventType = event.type;
        if (eventType == SDL_QUIT)
        {
            running = false;
        }
        else if (eventType == SDL_KEYUP)
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) 
            {
                running = false;
            }
            /*else if (key == SDLK_q) 
            {
                DestroyMainCamera();
            }*/
        }
        else if (eventType == SDL_WINDOWEVENT) // SDL_WINDOWEVENT_RESIZED)
        {
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
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

// void OpenWindow()
// {
//     int didFail = SetSDLAttributes(vsync);
//     PrintSDLDebug();
//     if (didFail == EXIT_FAILURE)
//     {
//         printf("Failed to SetSDLAttributes.");
//         headless = true;
//         return;
//     }
//     didFail = SpawnWindowSDL(fullscreen);
//     coreCount = SDL_GetCPUCount();
//     PrintOpenGL();
//     if (didFail == EXIT_FAILURE)
//     {
//         printf("Failed to SpawnWindowSDL.");
//         headless = true;
//         return;
//     }
//     // check open gl for failures?
//     didFail = LoadShaders();
//     if (didFail == EXIT_FAILURE)
//     {
//         printf("Failed to InitializeOpenGL.");
//         headless = true;
//     }
// }

/*if (UpdateEndTime())
{
    PrintBobSpawnSystem(world);
}*/

/*
I would recommend some sections on the quick start guide to flecs:
   An injection example for X x Y data reltionships, like many AIs linked to many Characters
   Disposing of allocated data in components examples
   Multithreading examples / section
   Bulk Spawning in threads (and example codes)
   A Simple Render system example, perhaps in a flecs.graphics module? This needs more thoughts
   Web Build guide with emcc (this isn't entirely needed but a nice to have)
*/
    // EmscriptenWebGLContextAttributes atrs;
    // emscripten_webgl_init_context_attributes(&atrs);
    // atrs.alpha = true;
    // atrs.depth = true;
    // atrs.stencil = false;
    // atrs.majorVersion = 3;
    // atrs.minorVersion = 0;
    // emctx = emscripten_webgl_create_context(id, &atrs);
    // emscripten_webgl_make_context_current(emctx);
