extern uint2 spawn_gpu_mesh_buffers();

// x is for indicies and verts
zox_component(MeshGPULink, uint2)

void add_gpu_mesh(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, MeshGPULink, { 0 })
}

void spawn_gpu_mesh(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set_only(e, MeshGPULink, { spawn_gpu_mesh_buffers() })
}

ECS_DTOR(MeshGPULink, ptr, {
    if (ptr->value.x != 0) glDeleteBuffers(1, &ptr->value.x);
    if (ptr->value.y != 0) glDeleteBuffers(1, &ptr->value.y);
})