#ifndef zoxel_apps
#define zoxel_apps

// zoxel apps: handles os windows, using (sdl, glut) libraries

// zoxel_settings
const char *icon_filepath;
#include "settings/settings.c"
// app variables
// zoxel_component_includes
zox_declare_tag(App)
// zoxel_prefab_includes
#include "prefabs/app.c"
// zoxel_util_includes
// sdl input sub module
#include "sdl/sdl.c"

void set_icon_filepath(const char *icon_filepath_new) {
    icon_filepath = icon_filepath_new;
}

void load_resources_apps(ecs_world_t *world) {
    load_resources_sdl(world);
}

void dispose_resources_apps(ecs_world_t *world) {
    dispose_resources_sdl(world);
}

unsigned char initialize_apps(ecs_world_t *world) {
    if (headless) return EXIT_SUCCESS;
    return initialize_apps_sdl(world);
}

void spawn_prefabs_apps(ecs_world_t *world) {
    spawn_prefab_app(world);
}

zox_begin_module(Apps)
// zoxel_component_defines
zox_define_tag(App)
#ifdef zox_include_vulkan
zox_define_component_w_dest(VulkanSurface)
#endif
zox_import_module(AppsSDL)
// zoxel_system_defines
zoxel_end_module(Apps)

#endif
