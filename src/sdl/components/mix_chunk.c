zoxc(SDLMixChunk, Mix_Chunk*);

ECS_DTOR(SDLMixChunk, ptr, {
    if (ptr->value) {
        // zee(ptr->value->abuf);
        zee(ptr->value);
    }
})