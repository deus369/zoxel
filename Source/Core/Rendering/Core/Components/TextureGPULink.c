//! Contains a link to the Texture on the GPU.
zoxel_component(TextureGPULink, GLuint);

extern GLuint SpawnTextureGPU();

void AddGPUTextureComponents(ecs_world_t *world, ecs_entity_t prefab)
{
    zoxel_set_component(world, prefab, TextureGPULink, { 0 });
}

void SpawnGPUTexture(ecs_world_t *world, ecs_entity_t e)
{
    ecs_set(world, e, TextureGPULink, { SpawnTextureGPU() });
}

ECS_DTOR(TextureGPULink, ptr,
{
    if (ptr->value != 0)
    {
        // printf("Deleting Texture on GPU.\n");
        glDeleteTextures(1, &ptr->value);
    }
})