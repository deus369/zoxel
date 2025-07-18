#ifndef zox_apps
#define zox_apps

// zoxel apps: handles os windows, using (sdl, glut) libraries
#include "components/_.c"
#include "settings/_.c"
#include "prefabs/_.c"
#include "util/_.c"

zox_begin_module(Apps)
    define_components_apps(world);
    add_hook_terminal_command(process_arguments_apps);
    initialize_settings_apps(world);
    spawn_prefabs_apps(world);
zox_end_module(Apps)

#endif