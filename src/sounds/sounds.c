#ifndef zox_mod_sounds
#define zox_mod_sounds

byte nosounds = 0;
#include "settings/_.c"
#include "data/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "sdl_mixer.c"
#include "io/_.c"
#include "util/_.c"
#include "instruments/_.c"
#include "systems/_.c"

void process_arguments_sounds(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        // zox_log("- arg %i [%s]", i, args[i])
        if (strcmp(args[i], "--nosound") == 0 || strcmp(args[i], "--nosounds") == 0) {
            nosounds = 1;
            zox_log("+ setting enabled [nosounds]")
        }
    }
}

zox_begin_module(Sounds)
    // ecs defines
    define_components_sounds(world);
    define_systems_sounds(world);
    // hooks
    zox_module_dispose(dispose_sounds)
    add_hook_terminal_command(process_arguments_sounds);
    // prefabs
    spawn_prefabs_sounds(world);
zox_end_module(Sounds)

#endif