#ifndef zox_apps
#define zox_apps

// zoxel apps: handles os windows, using (sdl, glut) libraries
#include "data/settings.c"
zox_declare_tag(App)
zox_component_byte(WindowFullscreen)
zox_component_int2(WindowSize)
zox_component_int2(WindowPosition)
zox_component_int2(WindowSizeRestore)

int2 get_window_position(int2 window_size, int2 screen_size) {
    if (window_size.x == screen_size.x && window_size.y == screen_size.y) {
        return (int2) { (screen_size.x) / 2, (screen_size.y) / 2 };
    } else {
        return (int2) { (screen_size.x - window_size.x) / 2, (screen_size.y - window_size.y) / 2 };
    }
}

#include "prefabs/app.c"
#include "sdl/sdl.c"

void apps_on_screen_resize(ecs_world_t *world, const int2 size) {
    if (fullscreen) {
        default_window_position = (int2) { (size.x) / 2, (size.y) / 2 };
    } else {
        zox_log(" > screen_dimensions.x: %i > %i\n", size.x, default_window_size.x)
        default_window_position = (int2) { (size.x - default_window_size.x) / 2, (size.y - default_window_size.y) / 2 };
    }
    zox_set(prefab_app_sdl, WindowPosition, { default_window_position })
}

void spawn_prefabs_apps(ecs_world_t *world) {
    spawn_prefab_app(world, default_window_position, default_window_size);
}

zox_begin_module(Apps)
if (headless) return;
zox_define_tag(App)
zox_define_component_byte(WindowFullscreen)
zox_define_component_int2(WindowSize)
zox_define_component_int2(WindowPosition)
zox_define_component_int2(WindowSizeRestore)
#ifdef zox_include_vulkan
zox_define_component(VulkanSurface)
#endif
spawn_prefabs_apps(world);
zox_import_module(AppsSDL)
apps_on_screen_resize(world, screen_dimensions);
zoxel_end_module(Apps)

#endif
