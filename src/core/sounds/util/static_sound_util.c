#ifdef zox_lib_sdl_mixer
/*
// MIX_DEFAULT_FORMAT https://wiki.libsdl.org/SDL2/SDL_AudioFormat

const char *sound_file_names[] = {
    resources_folder_name"sounds/bloop.wav",
	resources_folder_name"sounds/scratch.wav",
	resources_folder_name"sounds/high.wav",
	resources_folder_name"sounds/medium.wav",
	resources_folder_name"sounds/low.wav"
};
Mix_Chunk *sounds[static_sounds_length];

unsigned char load_static_sounds() {
#ifdef zox_disable_io
    return 1;
#endif
    unsigned char success = 1;
    for (int i = 0; i < static_sounds_length; i++) {
        sounds[i] = Mix_LoadWAV(sound_file_names[i]);
        if(sounds[i] == NULL) {
            zoxel_log("    - failed to load sound effect[%i]! SDL_mixer Error: %s\n", i, Mix_GetError());
            success = 0;
        }
    }
    return success;
}*/

/*void dispose_static_sounds() {
#ifdef zox_disable_io
    return;
#endif
    for (int i = 0; i < static_sounds_length; i++) Mix_FreeChunk(sounds[i]);
}*/

#endif
