zoxel_component(SDLSound, Mix_Chunk*);

ECS_DTOR(SDLSound, ptr,
{
    if (ptr->value != NULL)
    {
        // Mix_FreeChunk(ptr->value);
        if (sdlSound->value->abuf != NULL) {
            free(sdlSound->value->abuf);
        }
    }
})