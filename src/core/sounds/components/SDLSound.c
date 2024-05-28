#ifdef SDL_MIXER
// actually  its buffer is stored in SoundData so no need to Mix_FreeChunk
// ptr->value->abuf is just SoundData converted to (Uint8*)
zox_component(SDLSound, Mix_Chunk)

/*void free_sdl_sound(SDLSound *ptr) {
    if (ptr->value) free(ptr->value);
} ECS_DTOR(SDLSound, ptr, { free_sdl_sound(ptr); })*/

#endif
