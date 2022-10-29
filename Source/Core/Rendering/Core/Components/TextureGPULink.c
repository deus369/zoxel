//! Used to set the brightness of an entity.
ZOXEL_COMPONENT(TextureGPULink, GLuint);

extern GLuint SpawnTextureGPU();

void AddGPUTextureComponents(ecs_world_t *world, ecs_entity_t prefab)
{
    ecs_add(world, prefab, TextureGPULink);
    ecs_override(world, prefab, TextureGPULink);
    ecs_set(world, prefab, TextureGPULink, { 0 });
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