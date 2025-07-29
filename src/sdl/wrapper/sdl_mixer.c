// this is our sdl mixer wrapper!
// todo: move to sdl module
#ifdef zox_lib_sdl_mixer
#include <SDL2/SDL_mixer.h>

byte initialize_sdl_mixer(ulong sample_rate, byte channels_count) {
    if (Mix_OpenAudio(sample_rate, AUDIO_F32SYS, channels_count, 2048) < 0) {
        zox_log_error("sdl audio could not initialize [%s]\n", Mix_GetError())
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}

void close_audio_sdl() {
    // zox_log("- closing sdl_mixer");
    Mix_Quit();
}

int get_channels_count() {
    return Mix_GroupAvailable(-1);
}

byte sdl_play_sound(
    const float* data,
    const int length,
    const int channels,
    const float volume)
{
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

byte initialize_sdl_mixer() { return EXIT_FAILURE; }

void close_audio_sdl() { }

int get_channels_count() { return -1; }

byte sdl_play_sound(const SoundData *soundData, int channels, float volume) { return 1; }

SoundData process_mix_chunk(Mix_Chunk *mix_chunk) {
    return (SoundData) { .value = NULL, .length = 0 };
}

#endif