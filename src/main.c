#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "flecs/flecs.h"
// Modules
#include "Core/Core.h"
#include "Transforms2D/Transforms2D.h"
#include "Physics2D/Physics2D.h"
#include "Rendering/Rendering.h"
// Settings 
// \image html /screenshots/KEyHna.png width=50%
const bool isRendering = true;

void PrintSDLDebug()
{
    printf("Platform:        %s\n", SDL_GetPlatform());
    printf("CPU Count:       %d\n", SDL_GetCPUCount());
    printf("System RAM:      %d MB\n", SDL_GetSystemRAM());
    printf("Supports SSE:    %s\n", SDL_HasSSE() ? "true" : "false");
    printf("Supports SSE2:   %s\n", SDL_HasSSE2() ? "true" : "false");
    printf("Supports SSE3:   %s\n", SDL_HasSSE3() ? "true" : "false");
    printf("Supports SSE4.1: %s\n", SDL_HasSSE41() ? "true" : "false");
    printf("Supports SSE4.2: %s\n", SDL_HasSSE42() ? "true" : "false");
}

int bobCount = 0;
const int bobSpawnCount = 10000;
const float positionBounds = 0.1f;
const float velocityBounds = 4.4f;
const float torqueBounds = 8.0f;
const float2 scaleBounds = { 0.1f, 0.6f };
const float2 brightnessBounds = { 0.1f, 0.7f };

void SpawnBobArmy(ecs_world_t *world)
{
    ECS_COMPONENT(world, Position2D);
    ECS_COMPONENT(world, Rotation2D);
    ECS_COMPONENT(world, Velocity2D);
    ECS_COMPONENT(world, Torque2D);
    ECS_COMPONENT(world, Scale2D);
    ECS_COMPONENT(world, Brightness);
    // Create a SpaceShip prefab with a Defense component.
    const ecs_entity_t bobPrefab = ecs_new_prefab(world, "");
    ecs_add(world, bobPrefab, Position2D);
    ecs_add(world, bobPrefab, Velocity2D);
    ecs_add(world, bobPrefab, Rotation2D);
    ecs_add(world, bobPrefab, Torque2D);
    ecs_add(world, bobPrefab, Scale2D);
    ecs_add(world, bobPrefab, Brightness);
    Position2D *position2Ds = malloc(sizeof(Position2D) * bobSpawnCount);
    Velocity2D *velocity2Ds = malloc(sizeof(Velocity2D) * bobSpawnCount);
    // Rotation2D *rotation2Ds = malloc(sizeof(Rotation2D) * bobSpawnCount);
    Torque2D *torque2Ds = malloc(sizeof(Torque2D) * bobSpawnCount);
    Scale2D *scale2Ds = malloc(sizeof(Scale2D) * bobSpawnCount);
    Brightness *brightnesses = malloc(sizeof(Brightness) * bobSpawnCount);
    for (int i = 0; i < bobSpawnCount; i++)
    {
        position2Ds[i].value = (float2) {
            ((rand() % 101) / 100.0f) * positionBounds - (positionBounds / 2.0f),
            ((rand() % 101) / 100.0f) * positionBounds - (positionBounds / 2.0f)
        };
        velocity2Ds[i].value = (float2) {
            ((rand() % 101) / 100.0f) * velocityBounds - (velocityBounds / 2.0f),
            ((rand() % 101) / 100.0f) * velocityBounds - (velocityBounds / 2.0f)
        };
        torque2Ds[i].value = ((rand() % 101) / 100.0f) * torqueBounds - (torqueBounds / 2.0f);
        scale2Ds[i].value = scaleBounds.x + ((rand() % 101) / 100.0f) * (scaleBounds.y - scaleBounds.x);
        brightnesses[i].value = brightnessBounds.x + ((rand() % 101) / 100.0f) * (brightnessBounds.y - brightnessBounds.x);
    }
    const ecs_entity_t *bobArmy = ecs_bulk_init(world, &(ecs_bulk_desc_t)
    {
        .count = bobSpawnCount,
        .ids =
        {
            ecs_pair(EcsIsA, bobPrefab),
            ecs_id(Position2D),
            ecs_id(Velocity2D),
            ecs_id(Rotation2D),
            ecs_id(Torque2D),
            ecs_id(Scale2D),
            ecs_id(Brightness)
        },
        /* provide data for each id */
        .data = (void*[])
        {       
            NULL,       /* the pair doesn't have data */
            position2Ds,
            velocity2Ds,
            NULL, // rotation2Ds,
            torque2Ds,
            scale2Ds,
            brightnesses
        }
    });
    bobCount += bobSpawnCount;
}
/*ecs_set(world, bobPrefab, Position2D, { 0, 0 });
ecs_set(world, bobPrefab, Velocity2D, { 0, 0.04f });
ecs_set(world, bobPrefab, Torque2D, { 0 });
ecs_set(world, bobPrefab, Scale2D, { 1 });
ecs_set(world, bobPrefab, Brightness, { 1 });*/

void PrintHelpMenu(const char* arg0)
{
    printf("usage: %s [options]\n", arg0);
    printf("\n");
    printf("Options:\n");
    printf("  -h --help        print this help\n");
    printf("  -f --fullscreen  fullscreen window\n");
    printf("  -v --vsync       enable vsync\n");
    printf("  -p --profiler       enable profiler\n");
}

int main(int argc, char* argv[])
{
    bool fullscreen = false;
    bool vsync = false;
    bool profiler = false;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            PrintHelpMenu(argv[0]);
            return EXIT_SUCCESS;
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

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "failed to init SDL2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    PrintSDLDebug();
    // Request at least 32-bit color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Request a double-buffered, OpenGL 3.3 (or higher) core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    unsigned long flags = SDL_WINDOW_OPENGL;
    if (fullscreen) 
    {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    SDL_Window* window = SDL_CreateWindow("Zoxel",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        900, 640, flags);
    if (window == NULL)
    {
        SDL_Quit();
        fprintf(stderr, "failed to create SDL2 window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // SDL_GLContext is an alias for "void*"
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        fprintf(stderr, "failed to create OpenGL context: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    OpenGLInitialize(vsync);
    ecs_world_t *world = ecs_init_w_args(argc, argv);
    InitializeTransforms2D(world);
    InitializePhysics2D(world);
    if (isRendering)
    {
        InitializeRendering(world);
    }
    long framesPerSecond = 0;
    double time = 0.0;
    double deltaTime = 0.0;
    double lastTime = 0;
    double lastPrinted = 0.0;
    bool running = true;
    if (profiler)
    {
        ECS_IMPORT(world, FlecsMonitor); 
        ecs_singleton_set(world, EcsRest, {0});
    }
    if (!isRendering)
    {
        ecs_set_threads(world, SDL_GetCPUCount());
    }
    while (running)
    {
        time = SDL_GetTicks() / 1000.0;
        deltaTime = time - lastTime;
        lastTime = time;
        if (deltaTime == 0)
        {
            continue;
        }
        // input
        SDL_Event event = { 0 };
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
            {
                running = false;
            }
            if (event.type == SDL_KEYUP)
            {
                SDL_Keycode key = event.key.keysym.sym;
                if (key == SDLK_q || key == SDLK_ESCAPE) 
                {
                    running = false;
                }
                else if (key == SDLK_SPACE)
                {
                    SpawnBobArmy(world);
                }
            }
        }
        if (isRendering)
        {
            OpenGLBegin();
        }
        ecs_progress(world, deltaTime);
        if (isRendering)
        {
            OpenGLEnd();
        }
        if (time - lastPrinted >= 1.0)
        {
            lastPrinted = time;
            //printf("Time [%.18f]\n", deltaTime); // lu
            printf("Bob Count [%i]      FPS [%ld]\n", bobCount, framesPerSecond);
            //printf("    FPS: %ld\n", framesPerSecond);
            framesPerSecond = 0;
            // printf("    Bob's Position2D is {%f, %f}\n", position->value.x, position->value.y);
        }
        framesPerSecond++;
        if (isRendering)
        {
            SDL_GL_SwapWindow(window);
        }
    }
    ecs_fini(world);
    OpenGLEnded();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

    // for (int i = 0; i < bobSpawnCount; i++)
    // {
    //     float2 velocity2D = { 0, 0.01f };
    //     float2 position2D = { 0, 0 };
    //     position2D.x = ((rand() % 101) / 100.0f) * positionBounds - (positionBounds / 2.0f);
    //     position2D.y = ((rand() % 101) / 100.0f) * positionBounds - (positionBounds / 2.0f);
    //     ecs_set(world, e, Position2D, { position2D.x, position2D.y });
    //     velocity2D.x = ((rand() % 101) / 100.0f) * velocityBounds - (velocityBounds / 2.0f);
    //     velocity2D.y = ((rand() % 101) / 100.0f) * velocityBounds - (velocityBounds / 2.0f);
    //     float torque2D = ((rand() % 101) / 100.0f) * torqueBounds - (torqueBounds / 2.0f);
    //     float scale2D = scaleBounds.x + ((rand() % 101) / 100.0f) * (scaleBounds.y - scaleBounds.x);
    //     float brightness = brightnessBounds.x + ((rand() % 101) / 100.0f) * (brightnessBounds.y - brightnessBounds.x);
    //     // SpawnBob(world, position2D, velocity2D, torque2D, scale2D, brightness);
    //     ecs_entity_t e = bobArmy[i];
    //     ecs_set(world, e, Velocity2D, { velocity2D.x, velocity2D.y });
    //     // ecs_set(world, e, Rotation2D, { 0 });
    //     ecs_set(world, e, Torque2D, { torque2D });
    //     ecs_set(world, e, Scale2D, { scale2D });
    //     ecs_set(world, e, Brightness, { brightness });
    // }
    // Create a prefab instance
    //ecs_entity_t inst = ecs_new_entity(ecs, "BobClone");
    //ecs_add_pair(ecs, inst, EcsIsA, SpaceShip);
    // ecs_entity_t* bobArmy = ecs_bulk_init(world, &(ecs_bulk_desc_t));
    // ecs_add_pair(world, bobArmy, EcsIsA, bobPrefab);

// ecs_entity_t SpawnBob(ecs_world_t *world, float2 position2D, float2 velocity2D, float torque2D, float scale2D, float brightness)
// {
//     ECS_COMPONENT(world, Position2D);
//     ECS_COMPONENT(world, Rotation2D);
//     ECS_COMPONENT(world, Scale2D);
//     ECS_COMPONENT(world, Velocity2D);
//     ECS_COMPONENT(world, Torque2D);
//     ECS_COMPONENT(world, Brightness);
//     ecs_entity_t e = ecs_new_entity(world, "");
//     ecs_set(world, e, Position2D, { position2D.x, position2D.y });
//     ecs_set(world, e, Velocity2D, { velocity2D.x, velocity2D.y });
//     ecs_set(world, e, Rotation2D, { 0 });
//     ecs_set(world, e, Torque2D, { torque2D });
//     ecs_set(world, e, Scale2D, { scale2D });
//     ecs_set(world, e, Brightness, { brightness });
//     return e;
// }