zox_component(UboGPULink, GLuint)

void add_gpu_ubo(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_prefab_set(e, UboGPULink, { 0 })
}

void spawn_gpu_ubo(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, UboGPULink, { spawn_gpu_generic_buffer() })
}

// actually this gets called during flecs table changes
ECS_DTOR(UboGPULink, ptr, {
    // if (ptr->value != 0) glDeleteBuffers(1, &ptr->value);
})
