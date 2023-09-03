extern GLuint2 spawn_gpu_mesh_buffers();

// x is for indicies and verts
zox_component(MeshGPULink, GLuint2)

void add_gpu_mesh(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, MeshGPULink, { 0 })
}

void spawn_gpu_mesh(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set_only(e, MeshGPULink, { spawn_gpu_mesh_buffers() })
}

void clear_regular_buffer(GLuint *gpu_buffer) {
    if (gpu_buffer != 0) {
        glDeleteBuffers(1, gpu_buffer);
        *gpu_buffer = 0;
    }
}

ECS_DTOR(MeshGPULink, ptr, {
    if (ptr->value.x != 0) glDeleteBuffers(1, &ptr->value.x);
    if (ptr->value.y != 0) glDeleteBuffers(1, &ptr->value.y);
    // clear_gpu_mesh(&ptr->value);
    //clear_regular_buffer(&ptr->value.x);
    //clear_regular_buffer(&ptr->value.y);
    //if (ptr->value.x != 0) glDeleteBuffers(1, &ptr->value.x);
    //if (ptr->value.y != 0) glDeleteBuffers(1, &ptr->value.y);
})

/*void clear_gpu_mesh(GLuint2 *gpu_mesh) {
    if (gpu_mesh->x != 0) glDeleteBuffers(1, &gpu_mesh->x);
    if (gpu_mesh->y != 0) glDeleteBuffers(1, &gpu_mesh->y);
    gpu_mesh->x = 0;
    gpu_mesh->y = 0;
}*/