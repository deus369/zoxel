zoxel_component(TextureGPULink, GLuint)

extern GLuint spawn_gpu_texture_buffers();

void add_gpu_texture(ecs_world_t *world, ecs_entity_t prefab) {
    if (!headless) {
        zoxel_set(world, prefab, TextureGPULink, { 0 });
    }
}

void spawn_gpu_texture(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) {
        ecs_set(world, e, TextureGPULink, { spawn_gpu_texture_buffers() });
    }
}

ECS_DTOR(TextureGPULink, ptr, {
    if (ptr->value != 0) {
        glDeleteTextures(1, &ptr->value);
    }
})