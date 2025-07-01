#ifndef zox_mod_sounds
#define zox_mod_sounds

#include "_includes.c"
byte audio_enabled = 0;
#include "data/instrument_types.c"
#include "data/settings.c"
#include "components/components.c"
#include "prefabs/prefabs.c"
#include "util/util.c"
#include "instruments/instruments.c"
#include "systems/systems.c"

void initialize_sounds(ecs_world_t *world) {
#ifndef zox_lib_sdl_mixer
    zox_log(" ! sdl sounds are disabled\n")
    return;
#endif
    if (initialize_sdl_mixer() == EXIT_SUCCESS) {
        load_files_sounds();
        audio_enabled = 1;
    } else {
        zox_log(" ! audio files not loaded")
    }
}

void dispose_sounds(ecs_world_t *world, void *ctx) {
    dispose_files_sounds();
    close_audio_sdl();
}

zox_begin_module(Sounds)
    zox_module_dispose(dispose_sounds)
    define_components_sounds(world);
    define_systems_sounds(world);
    spawn_prefabs_sounds(world);    // make sure spawn before initializing
    initialize_sounds(world);
zox_end_module(Sounds)

#endif
