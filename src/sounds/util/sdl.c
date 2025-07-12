#ifdef zox_lib_sdl_mixer

int get_channels_count() {
    return Mix_GroupAvailable(-1);
}

byte sdl_play_sound(const float* data, const int length, const int channels, const float volume) {
    Mix_Chunk mix_chunk = (Mix_Chunk) {
        .volume = volume,
        .alen = length * sizeof(float),
        .abuf = (void*) data
    };
    if (Mix_PlayChannel(-1, &mix_chunk, 0) == -1) {
        zox_log_error(" ! failed to play sound: %s", Mix_GetError())
        return 0;
    } else {
        return 1;
    }
}

SoundData process_mix_chunk(Mix_Chunk *mix_chunk) {
    return (SoundData) {
        .value = (float*) mix_chunk->abuf,
        .length = mix_chunk->alen / sizeof(float)
    };
}

#else

int get_channels_count() { return -1; }

byte sdl_play_sound(const SoundData *soundData, int channels, float volume) { return 1; }

SoundData process_mix_chunk(Mix_Chunk *mix_chunk) {
    return (SoundData) { .value = NULL, .length = 0 };
}

#endif