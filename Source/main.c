// Add defines first
#include <stdbool.h>
#include <string.h>
#define SDL_IMAGES
// =-= F LECS =-=
// #define FLECS_C          /* C API convenience macros, always enabled */
#define FLECS_CUSTOM_BUILD
#define FLECS_MODULE        /* Module support */
#define FLECS_SYSTEM        /* System support */
#define FLECS_PIPELINE      /* Pipeline support */
#include "Imports/Flecs/flecs.h"
// =-= Modules =-=
// --- Core Core ---
#include "Core/Core/Core.c"
#include "Imports/Imports.c"
// --- Core ---
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

// Settings 
bool running = true;
bool isRendering = true;
bool headless = false;
bool fullscreen = false;
bool vsync = false;
bool profiler = false;
int hasSpawnedPlayer = 0;
ecs_entity_t localPlayer;

/*
I would recommend some sections on the quick start guide to flecs:
   An injection example for X x Y data reltionships, like many AIs linked to many Characters
   Disposing of allocated data in components examples
   Multithreading examples / section
   Bulk Spawning in threads (and example codes)
   A Simple Render system example, perhaps in a flecs.graphics module? This needs more thoughts
   Web Build guide with emcc (this isn't entirely needed but a nice to have)
*/

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
    ECS_IMPORT(world, Rendering);
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

//! This is a mistaken function. Move along.
int main(int argc, char* argv[])
{
    int didFail = ProcessArguments(argc, argv);
    if (didFail == EXIT_FAILURE)
    {
        return EXIT_SUCCESS;
    }
    int coreCount = 24;
    if (!headless)
    {
        didFail = InitializeSDL();
        PrintSDLDebug();
        if (didFail != EXIT_FAILURE)
        {
            didFail = SpawnWindowSDL(fullscreen);
            coreCount = SDL_GetCPUCount();
            PrintOpenGL();
            if (didFail != EXIT_FAILURE)
            {
                // check open gl for failures?
                didFail = InitializeOpenGL(vsync);
            }
        }
        if (didFail == EXIT_FAILURE)
        {
            printf("Failed to Open Window. Setting to headless mode.");
            headless = true;
        }
    }
    if (headless)
    {
        isRendering = false;
    }
    BeginTime();
    InitializeECS(argc, argv, profiler, true, coreCount);
    // Import Modules Here!
    ImportModules(world);
    // start game logic
    if (!headless)
    {
        SpawnMainCamera(screenDimensions);
        SpawnKeyboardEntity();
        localPlayer = SpawnPlayerCharacter2D(world);
    }
    //! Core Application Loop!
    while (running)
    {
        UpdateBeginTime();
        if (!headless)
        {
            UpdateBeginSDL();
            PollSDLEvents();
        }
        if (deltaTimeSDL > 0)
        {
            if (isRendering)
            {
                const float* viewMatrix = GetMainCameraViewMatrix();
                UpdateBeginOpenGL(viewMatrix);
            }
            UpdateECS();
            if (isRendering)
            {
                RunRendering(deltaTimeSDL);
                UpdateEndOpenGL();
                UpdateEndSDL();
            }
        }
        if (UpdateEndTime())
        {
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
            PrintBobSpawnSystem(world);
        }
    }
    EndECS();
    EndOpenGL();
    if (!headless)
    {
        EndSDL();
    }
    return EXIT_SUCCESS;
}

//! Temporary, quick and dirty events.
void PollSDLEvents()
{
    // BobArmySpawnFixer(world);   // until bug gets fixed
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
            else if (key == SDLK_q) 
            {
                DestroyMainCamera();
            }
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