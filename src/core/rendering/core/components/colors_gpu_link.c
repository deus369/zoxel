zoxel_component(ColorsGPULink, GLuint);

void add_gpu_colors(ecs_world_t *world, ecs_entity_t prefab) {
    if (!headless) {
        zox_set(prefab, ColorsGPULink, { 0 });
    }
}

void spawn_gpu_colors(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) {
        ecs_set(world, e, ColorsGPULink, { spawn_gpu_generic_buffer() });
    }
}

ECS_DTOR(ColorsGPULink, ptr, {
    if (ptr->value != 0) {
        glDeleteBuffers(1, &ptr->value);
        ptr->value = 0;
    }
})