#ifndef zoxel_apps_sdl
#define zoxel_apps_sdl

// when creating a sdl app
#include "util/import_sdl.c" // sdl is here
// #include "sdl/textures/textures.c"
// variables
const int sdl_fullscreen_byte = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN
SDL_Window* main_window;
SDL_GLContext* main_gl_context;
// zoxel_component_includes
zox_component(SDLWindow, SDL_Window*)
zox_component(Renderer, SDL_Renderer*)
zox_component(Context, SDL_GLContext*)
// zoxel_component_destroys
ECS_DTOR(SDLWindow, ptr, { if (ptr->value != 0) SDL_DestroyWindow(ptr->value); })
ECS_DTOR(Renderer, ptr, { if (ptr->value != 0) SDL_DestroyRenderer(ptr->value); })
ECS_DTOR(Context, ptr, { if (ptr->value != 0) SDL_GL_DeleteContext(ptr->value); })
// zoxel_prefab_includes
#include "prefabs/app_sdl.c"
#include "inputs/inputs.c"
#include "util/vulkan_util.c"
#include "util/sdl_util.c"
// extern void load_app_icon(SDL_Window* window, const char *icon_filepath);

void dispose_apps_sdl(ecs_world_t *world) {

}

void spawn_prefabs_apps_sdl(ecs_world_t *world) {
    spawn_prefab_app_sdl(world);
}

unsigned char initialize_apps_sdl(ecs_world_t *world) {
    debug_platform();
    spawn_prefab_app_sdl(world);
    initialize_sdl_video();
    initialize_apps_input(world);
    create_main_window(world);
    return EXIT_SUCCESS;
}

zox_begin_module(AppsSDL)
// zoxel_define_components
zox_define_component_w_dest(SDLWindow)
zox_define_component_w_dest(Context)
zox_define_component_w_dest(Renderer)
// sub modules
zox_import_module(AppsInputs)
zoxel_end_module(AppsSDL)

#endif
