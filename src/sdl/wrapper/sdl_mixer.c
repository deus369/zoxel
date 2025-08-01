// this is our sdl mixer wrapper!
// todo: move to sdl module
#ifdef zox_sdl_mixer

/*static void free_mix_chunk(int channel) {
    Mix_Chunk* chunk = Mix_GetChunk(channel);
    if (chunk) {
        // free(chunk);
    }
}*/

byte initialize_sdl_mixer(ulong sample_rate, byte channels_count) {
    if (Mix_OpenAudio(sample_rate, AUDIO_F32SYS, channels_count, 2048) < 0) {
        zox_log_error("sdl audio could not initialize [%s]\n", Mix_GetError());
        return EXIT_FAILURE;
    } else {
        // Mix_ChannelFinished(free_mix_chunk);
        return EXIT_SUCCESS;
    }
}

void close_audio_sdl() {
    Mix_Quit();
}

int get_channels_count() {
    return Mix_GroupAvailable(-1);
}

byte sdl_play_sound(
    SDLMixChunk* chunk,
    const float* data,
    const int length,
    const float volume,
    const int channel
) {
    if (!length || !volume || !data) {
        return 0;
    }
    if (!chunk->value) {
        chunk->value = malloc(sizeof(Mix_Chunk));
    }
    if (!chunk->value) {
        return 0;
    }
    *chunk->value = (Mix_Chunk) {
        .volume = (Uint8)(volume * 128.f),
        .alen = length * sizeof(float),
        .abuf = (void*) data,
    };
    if (Mix_PlayChannel(channel, chunk->value, 0) == -1) {
        zox_log_error("Failed to play sound: %s", Mix_GetError());
        return 0;
    }
    return 1;
}


byte sdl_play_sound2(
    const float* data,
    const int length,
    const float volume,
    const int channel)
{
    Mix_Chunk chunk = (Mix_Chunk) {
        .volume = volume,
        .alen = length * sizeof(float),
        .abuf = (void*) data,
    };
    int success = Mix_PlayChannel(channel, &chunk, 0);
    if (success == -1) {
        zox_log_error("Failed to play sound: %s", Mix_GetError());
    }
    return success != -1;
}

static inline float* zox_mix_chunk_samples(Mix_Chunk *mix_chunk) {
    return (float*) mix_chunk->abuf;
}

static inline int zox_mix_chunk_length(Mix_Chunk *mix_chunk) {
    return mix_chunk->alen / sizeof(float);
}

static inline double get_mix_chunk_sound_length(Mix_Chunk* chunk) {
    int frequency, channels;
    Uint16 format;
    if (Mix_QuerySpec(&frequency, &format, &channels) == 0) {
        // Oh dear, SDL_mixer isn't initialized or is being bashful
        zox_log_error("failed finding sound frequency (mix length)")
        return -1.0;
    }
    // The size of a sample in bytes
    int bytes_per_sample = ((SDL_AUDIO_BITSIZE(format) / 8) * channels);
    // The total length in seconds
    return (double) chunk->alen / (frequency * bytes_per_sample);
}

Mix_Chunk* clone_mix_chunk(const Mix_Chunk* original) {
    if (original == NULL) {
        // Can't clone what doesn't exist!
        zox_log_error("original Mix_Chunk null")
        return NULL;
    }
    // Allocate memory for the new chunk
    Mix_Chunk* clone = (Mix_Chunk*) malloc(sizeof(Mix_Chunk));
    if (clone == NULL) {
        // Alas, the memory allocation spell has failed
        zox_log_error("failed to allocate Mix_Chunk")
        return NULL;
    }
    // Copy the Mix_Chunk structure
    memcpy(clone, original, sizeof(Mix_Chunk));
    // Now, clone the actual sound data
    clone->abuf = (Uint8*) malloc(original->alen);
    if (clone->abuf == NULL) {
        // The cloning process stumbled at the final hurdle
        zox_log_error("failed to allocate abuf")
        free(clone);
        return NULL;
    }
    memcpy(clone->abuf, original->abuf, original->alen);
    return clone;
}


#else

byte initialize_sdl_mixer() {
    return EXIT_FAILURE;
}

void close_audio_sdl() { }

int get_channels_count() {
    return -1;
}

byte sdl_play_sound(const SoundData *soundData, int channels, float volume) {
    return 1;
}

SoundData process_mix_chunk(Mix_Chunk *mix_chunk) {
    return (SoundData) { .value = NULL, .length = 0 };
}

void spawn_mixer_pool(int max_buffers, int buffer_size) { }

void dispose_mixer_pool() { }

#endif