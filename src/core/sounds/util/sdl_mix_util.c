unsigned char load_audio_sdl() {
#ifndef SDL_MIXER
    return EXIT_FAILURE;
#else
    if(Mix_OpenAudio(sound_sample_rate, AUDIO_F32SYS, channels_count, 2048) < 0) {
#ifdef zoxel_debug_audio
        zox_log(" - sdl audio could not initialize [%s]\n", Mix_GetError())
#endif
        return EXIT_FAILURE;
    }
#ifdef zoxel_debug_audio
    zox_logg(" > sdl audio has initialized\n")
#endif
    return EXIT_SUCCESS;
#endif
}

void close_audio_sdl() {
#ifdef SDL_MIXER
    // dispose_static_sounds();
    Mix_Quit();
#endif
}
