#ifndef zoxel_apps
#define zoxel_apps
// #define debug_viewport_resize

//! Included Libraries for App
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#ifdef SDL_IMAGES
#include <SDL2/SDL_image.h>
#endif
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

//! apps Module.
bool vsync = false;
bool fullscreen = false;
bool halfscreen = false;
// Tags
ECS_DECLARE(App);
// components
zoxel_component(SDLWindow, SDL_Window*);
zoxel_component(Renderer, SDL_Renderer*);
zoxel_component(Context, SDL_GLContext*);
// prefabs
#include "prefabs/app.c"
/// Util
#include "util/sdl_util.c"
#include "util/flecs_util.c"
#include "util/cleanup_util.c"

//! Quits the application from running indefinitely.
void quit()
{
    running = false;
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #endif
}

extern void input_extract_from_sdl(ecs_world_t *world, SDL_Event event);
extern void resize_cameras(int width, int height);
extern void uis_on_viewport_resized(ecs_world_t *world, int width, int height);

void on_viewport_resized(int width, int height)
{
    #ifdef debug_viewport_resize
    printf("Viewport was resized [%ix%i]\n", width, height);
    #endif
    resize_viewports(width, height);
    resize_cameras(width, height);
    uis_on_viewport_resized(world, width, height);
}

//! Polls SDL for input events. Also handles resize and window quit events.
void update_sdl(ecs_world_t *world)
{
    SDL_Event event = { 0 };
    while (SDL_PollEvent(&event))
    {
        input_extract_from_sdl(world, event);
        int eventType = event.type;
        if (eventType == SDL_QUIT)
        {
            quit();
        }
        else if (eventType == SDL_KEYUP)
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) 
            {
                quit();
            }
        }
        else if (eventType == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                on_viewport_resized(event.window.data1, event.window.data2);
            }
        }
    }
}

//! Convert starting arguments to Settings.
int process_arguments(int argc, char* argv[])
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
        if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--halfscreen") == 0)
        {
            halfscreen = true;
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

void AppsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Apps);
    ECS_TAG_DEFINE(world, App);
    ECS_COMPONENT_DEFINE(world, SDLWindow);
    ECS_COMPONENT_DEFINE(world, Context);
    ECS_COMPONENT_DEFINE(world, Renderer);
    ecs_set_hooks(world, SDLWindow, { .dtor = ecs_dtor(SDLWindow) });
    ecs_set_hooks(world, Context, { .dtor = ecs_dtor(Context) });
    ecs_set_hooks(world, Renderer, { .dtor = ecs_dtor(Renderer) });
    spawn_app_prefab(world);
    // spawn app
    SDL_Window* window = spawn_sdl_window();
    SDL_GLContext* context = create_sdl_context(window);
    spawn_app(world, window, context);
}
#endif