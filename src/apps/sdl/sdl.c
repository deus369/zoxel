#ifndef zox_sdl
#define zox_sdl
// #define zox_log_screens
// #define zox_log_platform
#include "util/import_sdl.c" // sdl is here
const int sdl_fullscreen_byte = SDL_WINDOW_FULLSCREEN_DESKTOP; // SDL_WINDOW_FULLSCREEN
ecs_entity_t mouse_lock_window;
#include "components/components.c"
#include "prefabs/app_sdl.c"
#include "inputs/inputs.c"
#include "util/vulkan_util.c"
#include "util/sdl_opengl.c"
#include "util/screen.c"
#include "util/sdl_util.c"
#include "util/window.c"
#include "util/app_util.c"

void dispose_apps_sdl(ecs_world_t *world, void *ctx) {
    // dispose_sdl_cursor();
    close_sdl_input();
    close_sdl_video();
}

void spawn_prefabs_apps_sdl(ecs_world_t *world) {
    spawn_prefab_app_sdl(world);
}

unsigned char initialize_apps_sdl(ecs_world_t *world) {
#ifdef zox_log_platform
    debug_platform();
#endif
    initialize_sdl_video(world);
    screens_count = SDL_GetNumVideoDisplays();
    if (screens_count == 1) screen_index = 0;
    return EXIT_SUCCESS;
}

zox_begin_module(AppsSDL)
zox_module_dispose(dispose_apps_sdl)
zox_define_component_w_dest(SDLWindow)
zox_define_component_w_dest(Context)
zox_define_component_w_dest(Renderer)
initialize_apps_sdl(world);
spawn_prefabs_apps_sdl(world);
zox_import_module(AppsInputs)
zoxel_end_module(AppsSDL)

#endif
