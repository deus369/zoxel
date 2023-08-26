zox_component(UvsGPULink, GLuint)

void add_gpu_uvs(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, UvsGPULink, { 0 })
}

void spawn_gpu_uvs(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set_only(e, UvsGPULink, { spawn_gpu_generic_buffer() })
}

ECS_DTOR(UvsGPULink, ptr, {
    if (ptr->value != 0) glDeleteBuffers(1, &ptr->value);
})