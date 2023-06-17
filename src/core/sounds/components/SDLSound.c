zox_component(SDLSound, Mix_Chunk*);

void free_sdl_sound(SDLSound *ptr) {
    if (ptr->value != NULL) {
        Mix_FreeChunk(ptr->value);
        ptr->value = NULL;
    }
    /*if (ptr->value != NULL && ptr->value->abuf != NULL) {
        free(ptr->value->abuf);
        ptr->value = NULL;
    }*/
}

ECS_DTOR(SDLSound, ptr, { free_sdl_sound(ptr); })

// free(ptr->value->abuf);
// free(ptr->value);