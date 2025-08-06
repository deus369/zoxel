#ifndef zoxm_apps
#define zoxm_apps

// zoxel apps: handles os windows, using (sdl, glut) libraries
#include "components/_.c"
#include "settings/_.c"
#include "hooks/_.c"
#include "prefabs/_.c"
#include "util/_.c"
zox_increment_system_with_reset(WindowSizeDirty, zox_dirty_end);

zox_begin_module(Apps)
    define_components_apps(world);
    zox_define_increment_system(WindowSizeDirty, [none] App);
    add_hook_terminal_command(process_arguments_apps);
    initialize_settings_apps(world);
    add_hook_files_load(load_files_settings);
    spawn_prefabs_apps(world);
zox_end_module(Apps)

#endif