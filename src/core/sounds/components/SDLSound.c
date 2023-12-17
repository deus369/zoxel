#ifdef SDL_MIXER
// actually  its buffer is stored in SoundData so no need to Mix_FreeChunk

zox_component(SDLSound, Mix_Chunk*)
void free_sdl_sound(SDLSound *ptr) {
    if (ptr && ptr->value) {
        free(ptr->value);
        ptr->value = NULL;
    }
}
ECS_DTOR(SDLSound, ptr, { free_sdl_sound(ptr); })

#endif
