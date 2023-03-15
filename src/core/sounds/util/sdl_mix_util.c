unsigned char load_audio_sdl() {
    #ifdef SDL_MIXER
        // const int sample_rate = 44100;
        const int channels_count = 1;   // 2
        if(Mix_OpenAudio(sound_sample_rate, AUDIO_F32SYS, channels_count, 2048) < 0) {
            zoxel_log(" - sdl audio could not initialize [%s]\n", Mix_GetError());
            return EXIT_FAILURE;
        }
        /*if (!load_static_sounds())
        {
            success = 0;
        }*/
        zoxel_log(" + sdl audio has initialized\n");
        return EXIT_SUCCESS;
    #endif
    return EXIT_FAILURE;
}

void close_audio_sdl() {
    #ifdef SDL_MIXER
    dispose_static_sounds();
	Mix_Quit();
    #endif
}