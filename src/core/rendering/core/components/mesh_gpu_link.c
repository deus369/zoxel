extern GLuint2 spawn_gpu_mesh_buffers();

zox_component(MeshGPULink, GLuint2) // x is for indicies and verts

void add_gpu_mesh(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, MeshGPULink, { { 0, 0 } })
}

void spawn_gpu_mesh(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set_only(e, MeshGPULink, { spawn_gpu_mesh_buffers() })
}

ECS_DTOR(MeshGPULink, ptr, {
    if (ptr->value.x != 0) glDeleteBuffers(1, &ptr->value.x);
    if (ptr->value.y != 0) glDeleteBuffers(1, &ptr->value.y);
})

/*void clear_gpu_mesh(GLuint2 *gpu_mesh) {
    if (gpu_mesh->x != 0) glDeleteBuffers(1, &gpu_mesh->x);
    if (gpu_mesh->y != 0) glDeleteBuffers(1, &gpu_mesh->y);
    gpu_mesh->x = 0;
    gpu_mesh->y = 0;
}*/
// clear_gpu_mesh(&ptr->value);
// clear_regular_buffer(&ptr->value.x);
// clear_regular_buffer(&ptr->value.y);
//if (ptr->value.x != 0) glDeleteBuffers(1, &ptr->value.x);
//if (ptr->value.y != 0) glDeleteBuffers(1, &ptr->value.y);