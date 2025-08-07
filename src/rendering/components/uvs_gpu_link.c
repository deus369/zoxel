zox_component(UvsGPULink, uint)

void add_gpu_uvs(ecs *world, entity e) {
    if (!headless) zox_prefab_set(e, UvsGPULink, { 0 })
}

void spawn_gpu_uvs(ecs *world, entity e) {
    if (!headless) zox_set(e, UvsGPULink, { spawn_gpu_generic_buffer() })
}

ECS_DTOR(UvsGPULink, ptr, {
    if (ptr->value != 0) glDeleteBuffers(1, &ptr->value);
})