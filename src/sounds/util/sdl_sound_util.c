#ifdef zox_lib_sdl_mixer

double get_mix_chunk_sound_length(Mix_Chunk* chunk) {
    int frequency, channels;
    Uint16 format;
    if (Mix_QuerySpec(&frequency, &format, &channels) == 0) {
        // Oh dear, SDL_mixer isn't initialized or is being bashful
        return -1.0;
    }
    // The size of a sample in bytes
    int bytes_per_sample = ((SDL_AUDIO_BITSIZE(format) / 8) * channels);
    // The total length in seconds
    double length = (double)chunk->alen / (frequency * bytes_per_sample);
    return length;
}

Mix_Chunk* clone_mix_chunk(const Mix_Chunk* original) {
    if (original == NULL) {
        // Can't clone what doesn't exist!
        return NULL;
    }
    // Allocate memory for the new chunk
    Mix_Chunk* clone = (Mix_Chunk*)malloc(sizeof(Mix_Chunk));
    if (clone == NULL) {
        // Alas, the memory allocation spell has failed
        return NULL;
    }
    // Copy the Mix_Chunk structure
    memcpy(clone, original, sizeof(Mix_Chunk));
    // Now, clone the actual sound data
    clone->abuf = (Uint8*)malloc(original->alen);
    if (clone->abuf == NULL) {
        // The cloning process stumbled at the final hurdle
        free(clone);
        return NULL;
    }
    memcpy(clone->abuf, original->abuf, original->alen);
    return clone;
}

#endif
