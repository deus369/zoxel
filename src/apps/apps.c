#ifndef zox_apps
#define zox_apps

// zoxel apps: handles os windows, using (sdl, glut) libraries
#include "data/settings.c"
zox_declare_tag(App)
zox_component_byte(WindowFullscreen)
zox_component_int2(WindowSize)
zox_component_int2(WindowPosition)
zox_component_int2(WindowSizeRestore)
#include "util/screen.c"
#include "prefabs/app.c"
#include "sdl/sdl.c"

void spawn_prefabs_apps(ecs_world_t *world) {
    spawn_prefab_app(world, default_window_position, default_window_size);
}

zox_begin_module(Apps)
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
set_app_screen_resize(world, prefab_app_sdl, screen_dimensions);
zoxel_end_module(Apps)

#endif
