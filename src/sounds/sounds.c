#ifndef zox_mod_sounds
#define zox_mod_sounds

byte is_log_sounds = 0;

#define zox_log_sounds(msg, ...)\
    if (is_log_sounds) { zox_log(msg, ##__VA_ARGS__) }

#ifdef zox_lib_sdl_mixer
    #if defined(zox_lib_sdl_direct)
        #include <SDL_mixer.h>
    #else
        #include <SDL2/SDL_mixer.h>
    #endif
#endif
#include "data/instrument_types.c"
#include "data/settings.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "instruments/_.c"
#include "systems/_.c"
#include "io/_.c"

void dispose_sounds(ecs_world_t *world, void *ctx) {
    dispose_files_sounds();
    close_audio_sdl();
}

zox_begin_module(Sounds)
    zox_module_dispose(dispose_sounds)
    define_components_sounds(world);
    define_systems_sounds(world);
    spawn_prefabs_sounds(world);
    initialize_sounds(world);
zox_end_module(Sounds)

#endif