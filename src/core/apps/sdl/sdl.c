#ifndef zoxel_apps_sdl
#define zoxel_apps_sdl

#include "util/import_sdl.c" // sdl is here
const int sdl_fullscreen_byte = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN
SDL_Window* main_window;
SDL_GLContext* main_gl_context;
zox_component(SDLWindow, SDL_Window*)
zox_component(Renderer, SDL_Renderer*)
zox_component(Context, SDL_GLContext*)
ECS_DTOR(SDLWindow, ptr, { if (ptr->value != 0) SDL_DestroyWindow(ptr->value); })
ECS_DTOR(Renderer, ptr, { if (ptr->value != 0) SDL_DestroyRenderer(ptr->value); })
ECS_DTOR(Context, ptr, { if (ptr->value != 0) SDL_GL_DeleteContext(ptr->value); })
#include "prefabs/app_sdl.c"
#include "inputs/inputs.c"
#include "util/vulkan_util.c"
#include "util/sdl_util.c"

void dispose_apps_sdl(ecs_world_t *world) {
    dispose_sdl_cursor();
}

void spawn_prefabs_apps_sdl(ecs_world_t *world) {
    spawn_prefab_app_sdl(world);
}

unsigned char initialize_apps_sdl(ecs_world_t *world) {
    debug_platform();
    spawn_prefab_app_sdl(world);
    initialize_sdl_video();
    initialize_apps_input(world);
    screens_count = SDL_GetNumVideoDisplays();
    if (screens_count == 1) screen_index = 0;
    create_main_window(world);
    return EXIT_SUCCESS;
}

zox_begin_module(AppsSDL)
zox_define_component_w_dest(SDLWindow)
zox_define_component_w_dest(Context)
zox_define_component_w_dest(Renderer)
zox_import_module(AppsInputs)
zoxel_end_module(AppsSDL)

#endif
