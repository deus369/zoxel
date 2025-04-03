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
#include "util/arguments.c"
#include "prefabs/prefabs.c"

zox_begin_module(Apps)
    add_hook_terminal_command(process_arguments_apps);
    zox_define_tag(App)
    zox_define_component_byte(WindowFullscreen)
    zox_define_component_int2(WindowSize)
    zox_define_component_int2(WindowPosition)
    zox_define_component_int2(WindowSizeRestore)
    #ifdef zox_include_vulkan
    zox_define_component(VulkanSurface)
    #endif
    spawn_prefabs_apps(world);
zox_end_module(Apps)

#endif
