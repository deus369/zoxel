#include "vulkan.c"
#include "sdl_opengl.c"
#include "screen.c"
#include "sdl.c"
#include "window.c"
#include "app.c"
#include "app_vulkan.c"

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
    return EXIT_SUCCESS;
}