zox_component(ColorsGPULink, GLuint)

void add_gpu_colors(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_prefab_set(e, ColorsGPULink, { 0 })
}

void spawn_gpu_colors(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, ColorsGPULink, { spawn_gpu_generic_buffer() })
}

ECS_DTOR(ColorsGPULink, ptr, {
    if (ptr->value) glDeleteBuffers(1, &ptr->value);
})
