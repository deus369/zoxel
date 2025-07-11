byte initialize_sdl_mixer() {
#ifndef zox_lib_sdl_mixer
    return EXIT_FAILURE;
#else
    if (Mix_OpenAudio(channel_sample_rate, AUDIO_F32SYS, channels_count, 2048) < 0) {
    #ifdef zoxel_debug_audio
        zox_log(" - sdl audio could not initialize [%s]\n", Mix_GetError())
    #endif
        return EXIT_FAILURE;
    }
    // int channel_available = Mix_GroupAvailable(-1); // -1 indicates all channels
    // if (channel_available >= 0) zox_log(" + sdl channel available [%i]\n", channel_available);
    return EXIT_SUCCESS;
#endif
}

void close_audio_sdl() {
#ifdef zox_lib_sdl_mixer
    zox_log_sounds("> Mix_Quit")
    Mix_Quit();
#endif
}

void initialize_sounds(ecs_world_t *world) {
    if (initialize_sdl_mixer() == EXIT_SUCCESS) {
        audio_enabled = 1;
        zox_log_sounds("> initialize_sdl_mixer success")
    } else {
        zox_log_error("[initialize_sdl_mixer] failed")
    }
}
