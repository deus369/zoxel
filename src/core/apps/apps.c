#ifndef zoxel_apps
#define zoxel_apps

//! apps Module.
const int window_index = 1; // 1;
bool vsync = false;
bool fullscreen = true; // full screen is the new default option
bool halfscreen = false;
bool is_split_screen = false;
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
#include "util/flecs_util.c"
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