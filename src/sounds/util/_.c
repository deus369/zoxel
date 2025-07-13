#include "note_frequencies.c"
#include "sin_waves.c"
#include "square_waves.c"
#include "triangle_waves.c"
#include "sawtooth_waves.c"
#include "fm_synthesis_waves.c"
#include "noise_waves.c"
#include "envelop.c"
#include "spawn.c"

void initialize_sounds(ecs_world_t *world) {
    if (initialize_sdl_mixer() == EXIT_SUCCESS) {
        audio_enabled = 1;
        zox_log_sounds("> initialize_sdl_mixer success")
    } else {
        zox_log_error("[initialize_sdl_mixer] failed")
    }
}

void dispose_sounds(ecs_world_t *world, void *ctx) {
    dispose_files_sounds();
    close_audio_sdl();
}