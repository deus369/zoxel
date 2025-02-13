#include "vulkan_util.c"
#include "sdl_opengl.c"
#include "screen.c"
#include "sdl_util.c"
#include "window.c"
#include "app_util.c"

void dispose_apps_sdl(ecs_world_t *world, void *ctx) {
    // dispose_sdl_cursor();
    close_sdl_input();
    close_sdl_video();
}

byte initialize_apps_sdl(ecs_world_t *world) {
    #ifdef zox_log_platform
    debug_platform();
    #endif
    initialize_sdl_video(world);
    screens_count = SDL_GetNumVideoDisplays();
    if (screens_count == 1) screen_index = 0;
    return EXIT_SUCCESS;
}