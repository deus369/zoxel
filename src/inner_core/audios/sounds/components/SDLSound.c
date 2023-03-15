zoxel_component(SDLSound, Mix_Chunk*);

ECS_DTOR(SDLSound, ptr,
{
    if (ptr->value != NULL)
    {
        // Mix_FreeChunk(ptr->value);
        if (ptr->value->abuf != NULL) {
            free(ptr->value->abuf);
        }
    }
})