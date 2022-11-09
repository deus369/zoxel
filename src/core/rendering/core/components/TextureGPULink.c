//! Contains a link to the Texture on the GPU.
zoxel_component(TextureGPULink, GLuint);

extern GLuint spawn_gpu_texture_buffers();

void add_gpu_texture(ecs_world_t *world, ecs_entity_t prefab)
{
    zoxel_set_component(world, prefab, TextureGPULink, { 0 });
}

void spawn_gpu_texture(ecs_world_t *world, ecs_entity_t e)
{
    ecs_set(world, e, TextureGPULink, { spawn_gpu_texture_buffers() });
}

ECS_DTOR(TextureGPULink, ptr,
{
    if (ptr->value != 0)
    {
        // printf("Deleting Texture on GPU.\n");
        glDeleteTextures(1, &ptr->value);
    }
})