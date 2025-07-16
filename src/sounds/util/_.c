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

#include "spawn.c"
#include "setting.c"
#include "terminal.c"