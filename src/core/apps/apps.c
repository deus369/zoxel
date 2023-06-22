#ifndef zoxel_apps
#define zoxel_apps

// zoxel_settings
#define sdl_gl_major 3
#define sdl_gl_minor 0
unsigned char running;
unsigned char rendering = 1;
unsigned char headless = 0;
unsigned char vsync = 1;
unsigned char fullscreen = 1; // set full screen default option here
unsigned char halfscreen = 0;
unsigned char is_split_screen = 0;
unsigned char override_opengl_es = 0;
unsigned char is_vulkan = 0;
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
#include "util/path_util.c"
#include "util/terminal_util.c"
#include "util/sdl_util.c"
#include "util/webasm_util.c"
#include "util/cleanup_util.c"
#include "util/mouse_util.c"
#include "util/platform_util.c"

unsigned char initialize_apps(ecs_world_t *world) {
    init_sdl();
    initialize_pathing();
    unsigned char is_vulkan_supported = vulkan_supported();
    if (is_vulkan && !is_vulkan_supported) is_vulkan = 0;
    debug_platform();
    print_sdl();
    return create_main_window(world);
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
