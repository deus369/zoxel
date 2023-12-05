zox_component(SDLSound, Mix_Chunk*)

// actually  its buffer is stored in SoundData so no need to free entire mix chunk
// Mix_FreeChunk(ptr->value);

void free_sdl_sound(SDLSound *ptr) {
    if (ptr && ptr->value) {
        // zox_logg(" > clearing SDLSound\n")
        free(ptr->value);
        ptr->value = NULL;
    }
}

ECS_DTOR(SDLSound, ptr, { free_sdl_sound(ptr); })
