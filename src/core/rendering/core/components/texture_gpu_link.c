extern GLuint spawn_gpu_texture_buffers();

zox_component(TextureGPULink, GLuint)

void add_gpu_texture(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, TextureGPULink, { 0 });
}

void spawn_gpu_texture(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set_only(e, TextureGPULink, { spawn_gpu_texture_buffers() })
}

ECS_DTOR(TextureGPULink, ptr, {
    if (ptr->value != 0) glDeleteTextures(1, &ptr->value);
})