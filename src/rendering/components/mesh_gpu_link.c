extern uint2 spawn_gpu_mesh_buffers();

zox_component(MeshGPULink, uint2); // x is for indicies and verts

void add_gpu_mesh(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) {
        zox_prefab_set(e, MeshGPULink, { { 0, 0 } });
    }
}

void spawn_gpu_mesh(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) {
        zox_set(e, MeshGPULink, { spawn_gpu_mesh_buffers() });
    }
}

ECS_DTOR(MeshGPULink, ptr, {
    if (ptr->value.x) {
        glDeleteBuffers(1, &ptr->value.x);
    }
    if (ptr->value.y) {
        glDeleteBuffers(1, &ptr->value.y);
    }
})