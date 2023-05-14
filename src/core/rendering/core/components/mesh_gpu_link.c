// x is for indicies and verts
zoxel_component(MeshGPULink, GLuint2)

void add_gpu_mesh(ecs_world_t *world, ecs_entity_t prefab) {
    if (!headless) {
        zox_set(prefab, MeshGPULink, { 0 });
    }
}

//! Grab from opengl part.
extern GLuint2 spawn_gpu_mesh_buffers();

void spawn_gpu_mesh(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) {
        ecs_set(world, e, MeshGPULink, { spawn_gpu_mesh_buffers() });
    }
}

ECS_DTOR(MeshGPULink, ptr, {
    if (ptr->value.x != 0) {
        glDeleteBuffers(1, &ptr->value.x);
        ptr->value.x = 0;
    }
    if (ptr->value.y != 0) {
        glDeleteBuffers(1, &ptr->value.y);
        ptr->value.y = 0;
    }
})