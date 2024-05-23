#ifndef zox_apps
#define zox_apps

// zoxel apps: handles os windows, using (sdl, glut) libraries
#include "data/settings.c"
zox_declare_tag(App)
zox_component_byte(WindowFullscreen)
zox_component_int2(WindowSize)
zox_component_int2(WindowPosition)
#include "prefabs/app.c"
#include "sdl/sdl.c"

void spawn_prefabs_apps(ecs_world_t *world) {
    // sets to middle of screen
    default_window_position = (int2) { screen_dimensions.x / 2 - default_window_size.x / 2, screen_dimensions.y / 2 - default_window_size.y / 2 };
    spawn_prefab_app(world, default_window_position, default_window_size);
}

zox_begin_module(Apps)
if (headless) return;
zox_define_tag(App)
zox_define_component_byte(WindowFullscreen)
zox_define_component_int2(WindowSize)
zox_define_component_int2(WindowPosition)
#ifdef zox_include_vulkan
zox_define_component(VulkanSurface)
#endif
spawn_prefabs_apps(world);
zox_import_module(AppsSDL)
zoxel_end_module(Apps)

#endif
