zox_component(TextureGPULink, uint)

extern uint spawn_gpu_texture_buffers();

void add_gpu_texture(ecs_world_t *world, ecs_entity_t prefab) {
    if (!headless) zox_set(prefab, TextureGPULink, { 0 });
}

void spawn_gpu_texture(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) ecs_set(world, e, TextureGPULink, { spawn_gpu_texture_buffers() });
}

ECS_DTOR(TextureGPULink, ptr, {
    if (ptr->value != 0) glDeleteTextures(1, &ptr->value);
})