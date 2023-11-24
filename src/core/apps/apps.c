#ifndef zoxel_apps
#define zoxel_apps

// zoxel apps: handles os windows, using (sdl, glut) libraries

// zoxel_settings
#include "settings/settings.c"
// app variables
#ifdef zoxel_include_vulkan
    VkInstance* main_vulkan_instance;
    VkSurfaceKHR* main_vulkan_context;
#endif
// zoxel_component_includes
zox_declare_tag(App)
#ifdef zoxel_include_vulkan
    zox_component(VulkanSurface, VkSurfaceKHR*)
    ECS_DTOR(VulkanSurface, ptr, { if (ptr->value != 0) vkDestroySurfaceKHR(*main_vulkan_instance, *ptr->value, NULL); })
#endif
// zoxel_prefab_includes
#include "prefabs/app.c"
// zoxel_util_includes
// sdl input sub module
#include "sdl/sdl.c"

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
#ifdef zoxel_include_vulkan
zox_define_component_w_dest(VulkanSurface)
#endif
zox_import_module(AppsSDL)
// zoxel_system_defines
zoxel_end_module(Apps)

#endif
