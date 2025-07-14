#ifndef zox_apps
#define zox_apps

// zoxel apps: handles os windows, using (sdl, glut) libraries
#include "settings/_.c"
#include "components/_.c"
#include "util/_.c"
#include "prefabs/_.c"

zox_begin_module(Apps)
    define_components_apps(world);
    spawn_prefabs_apps(world);
    add_hook_terminal_command(process_arguments_apps);
zox_end_module(Apps)

#endif