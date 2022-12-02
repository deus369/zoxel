#ifndef zoxel_core
#define zoxel_core

//! Included Libraries for App
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef USE_SDL_3
    #include <SDL3/SDL.h>
    #include <SDL3/SDL_opengl.h>
#else
    #ifdef ANDROID_BUILD
        #include <SDL.h>
        #include <SDL_opengl.h>
    #else
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_opengl.h>
    #endif
#endif
#ifdef ANDROID_BUILD
    #ifdef SDL_IMAGES
        #include <SDL_image.h>
    #endif
#else
    #ifdef SDL_IMAGES
        #include <SDL2/SDL_image.h>
    #endif
#endif

// Settings for main
bool headless = false;
bool running = true;
bool profiler = false;
// --- core ---
#include "maths/maths.c"
#include "generic/generic.c"
#include "apps/apps.c"
#include "inputs/inputs.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "cameras/cameras.c"
#include "rendering/rendering.c"

//! The main update loop.
void update_core()
{
    // apps / Input events
    if (!headless)
    {
        reset_input_devices(world);
        update_sdl(world);
        #ifdef __EMSCRIPTEN__
        if (update_web_canvas(world))
        {
            // return;
        }
        #endif
    }
    // ecs_log_set_level(1);    // use this to debug system pipelines
    ecs_progress(world, 0);
    // main thread, generates gpu buffer
    if (!headless)
    {
        set_mouse_mode();
        render_loop_temp();
    }
}

int begin_core(int argc, char* argv[])
{
    int didFail = process_arguments(argc, argv);
    if (didFail == EXIT_FAILURE)
    {
        return EXIT_SUCCESS;
    }
    open_ecs(argc, argv, profiler); // begin ecs
    return 0;
}

void close_core()
{
    close_ecs();
    if (!headless)
    {
        dispose_opengl();
        sdl_on_end();
    }
}

void CoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, Core);
    ECS_IMPORT(world, Generic);
    ECS_IMPORT(world, Maths);
    if (!headless)
    {
        ECS_IMPORT(world, Apps);
    }
    ECS_IMPORT(world, Inputs);
    ECS_IMPORT(world, Timing);
    ECS_IMPORT(world, Transforms);
    if (!headless)
    {
        ECS_IMPORT(world, Rendering);
    }
    ECS_IMPORT(world, Cameras);
}
#endif