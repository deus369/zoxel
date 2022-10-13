#include <stdbool.h>
#include <string.h>
#define SDL_IMAGES
#include "Imports/Imports.h"
// --- Core ---
#include "Core/Core/Core.h"
#include "Core/Inputs/Inputs.h"
#include "Core/Transforms2D/Transforms2D.h"
#include "Core/Transforms/Transforms.h"
#include "Core/Rendering/Rendering.h"
#include "Core/Cameras/Cameras.h"
#include "Core/Textures/Textures.h"
#include "Core/Voxels/Voxels.h"
// --- Space ---
#include "Space/Physics2D/Physics2D.h"
// --- Gameplay ---
#include "Core/Players/Players.h"

// Settings 
bool running = true;
const bool isRendering = true;
bool fullscreen = false;
bool vsync = false;
bool profiler = false;

// Forward  Declares
int ProcessArguments(int argc, char* argv[]);
void PollSDLEvents();

void InitializeModules(ecs_world_t *world)
{
    // Core Modules
    ECS_IMPORT(world, Inputs);
    ECS_IMPORT(world, Transforms2D);
    ECS_IMPORT(world, Transforms);
    if (isRendering)
    {
        ECS_IMPORT(world, Rendering);
    }
    ECS_IMPORT(world, Cameras);
    ECS_IMPORT(world, Textures);
    ECS_IMPORT(world, Voxels);
    // Space Modules
    ECS_IMPORT(world, Physics2D);
    // Gameplay Modules
    ECS_IMPORT(world, Players);

    // Spawn things from Modules
    InitializeInputs(world);
    InitializePlayers(world);
    InitializeCameras(world);
    // InitializeVoxels(world);
}

//! This is a mistaken function. Move along.
int main(int argc, char* argv[])
{
    int didFail = ProcessArguments(argc, argv);
    if (didFail == EXIT_FAILURE)
    {
        return EXIT_SUCCESS;
    }
    didFail = InitializeSDL();
    if (didFail == EXIT_FAILURE)
    {
        return didFail;
    }
    didFail = SpawnWindowSDL(fullscreen);
    if (didFail == EXIT_FAILURE)
    {
        return didFail;
    }
    InitializeOpenGL(vsync);
    ecs_world_t *world = InitializeECS(argc, argv, profiler, isRendering);
    // Import Modules Here!
    InitializeModules(world);

    deltaTimeSDL = 0;
    //! Core Application Loop!
    while (running)
    {
        UpdateBeginSDL();
        PollSDLEvents();
        if (deltaTimeSDL > 0)
        {
            if (isRendering)
            {
                UpdateBeginOpenGL();
            }
            UpdateECS();
            if (isRendering)
            {
                UpdateEndOpenGL();
            }
        }
        UpdateEndSDL(isRendering);
    }
    EndECS();
    EndOpenGL();
    EndSDL();
    return EXIT_SUCCESS;
}

//! Temporary, quick and dirty events.
void PollSDLEvents()
{
    BobArmySpawnFixer(world);   // until bug gets fixed
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
            if (key == SDLK_q || key == SDLK_ESCAPE) 
            {
                running = false;
            }
        }
        else if (eventType == SDL_WINDOWEVENT) // SDL_WINDOWEVENT_RESIZED)
        {
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                ResizeOpenGL(event.window.data1, event.window.data2);
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
    }
    return EXIT_SUCCESS;
}