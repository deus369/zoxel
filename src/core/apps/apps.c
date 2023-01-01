#ifndef zoxel_apps
#define zoxel_apps

// app includes
#ifdef WEB_BUILD
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

//! apps Module.
const int window_index = 1; // 1;
unsigned char vsync = 0;
unsigned char fullscreen = 1; // full screen is the new default option
unsigned char halfscreen = 0;
unsigned char is_split_screen = 0;
SDL_Window* main_window;
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
#include "util/cleanup_util.c"

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
    set_data_path();
    // spawn app
    SDL_Window* window = spawn_sdl_window();
    SDL_GLContext* context = create_sdl_context(window);
    spawn_app(world, window, context);
    main_window = window;
    #ifndef WEB_BUILD
        #ifndef ANDROID_BUILD
            if (fullscreen) 
            {
                sdl_toggle_fullscreen(main_window);
            }
        #endif
    #endif
}
#endif