//! Contains a link to the MaterialGPULink on the GPU.
/**
*   Materials are shader program instances.
*   \todo Seperate mesh data into different files.
*/
zox_component(UvsGPULink, uint) // uint);

void add_gpu_uvs(ecs_world_t *world, ecs_entity_t prefab) {
    if (!headless) {
        zox_set(prefab, UvsGPULink, { 0 });
    }
}

void spawn_gpu_uvs(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) {
        ecs_set(world, e, UvsGPULink, { spawn_gpu_generic_buffer() });
    }
}

ECS_DTOR(UvsGPULink, ptr, {
    if (ptr->value != 0) {
        glDeleteBuffers(1, &ptr->value);
        ptr->value = 0;
    }
})