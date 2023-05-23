zoxel_component(SDLSound, Mix_Chunk*);

void free_sdl_sound(SDLSound *ptr) {
    if (ptr->value != NULL && ptr->value->abuf != NULL) {
        Mix_FreeChunk(ptr->value);
        ptr->value = NULL;
    }
}

ECS_DTOR(SDLSound, ptr, {
    free_sdl_sound(ptr);
})

// free(ptr->value->abuf);
// free(ptr->value);