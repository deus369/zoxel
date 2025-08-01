zox_component(SDLMixChunk, Mix_Chunk*);

ECS_DTOR(SDLMixChunk, ptr, {
    if (ptr->value) {
        free(ptr->value);
    }
})