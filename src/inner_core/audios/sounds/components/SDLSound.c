zoxel_component(SDLSound, Mix_Chunk*);

ECS_DTOR(SDLSound, ptr,
{
    if (ptr->value != NULL)
    {
        // printf("Freeing SDLSound.\n");
        Mix_FreeChunk(ptr->value);
    }
})