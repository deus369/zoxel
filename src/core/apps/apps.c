#ifndef zoxel_apps
#define zoxel_apps

#include "util/import_sdl.c" // sdl is here
// zoxel_settings
#include "settings/settings.c"
// app variables
SDL_Window* main_window;
SDL_GLContext* main_gl_context;
#ifdef zoxel_include_vulkan
    VkInstance* main_vulkan_instance;
    VkSurfaceKHR* main_vulkan_context;
#endif
// zoxel_component_includes
zox_declare_tag(App)
zox_component(SDLWindow, SDL_Window*)
zox_component(Renderer, SDL_Renderer*)
zox_component(Context, SDL_GLContext*)
#ifdef zoxel_include_vulkan
    zox_component(VulkanSurface, VkSurfaceKHR*)
#endif
// zoxel_prefab_includes
#include "prefabs/app.c"
// zoxel_util_includes
#include "util/main_loop_util.c"
#include "util/app_icon.c"
#include "util/cleanup_util.c"
#include "util/mouse_util.c"
// sdl input sub module
#include "sdl/inputs/inputs.c"
// the rest?
#include "util/sdl_util.c"

unsigned char initialize_apps(ecs_world_t *world) {
    if (headless) return EXIT_SUCCESS;
    debug_platform();
    initialize_sdl();
    create_main_window(world);
    return EXIT_SUCCESS;
}

void spawn_prefabs_apps(ecs_world_t *world) {
    spawn_prefab_app(world);
}

zox_begin_module(Apps)
// zoxel_component_defines
zox_define_tag(App)
zox_define_component_w_dest(SDLWindow)
zox_define_component_w_dest(Context)
zox_define_component_w_dest(Renderer)
#ifdef zoxel_include_vulkan
    zox_define_component_w_dest(VulkanSurface)
#endif
// zoxel_system_defines
zoxel_end_module(Apps)

#endif
