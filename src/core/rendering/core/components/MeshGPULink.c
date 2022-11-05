//! Contains a link to the MaterialGPULink on the GPU.
/**
*   Materials are shader program instances.
*   \todo Seperate mesh data into different files.
*/
zoxel_component(MeshGPULink, GLuint2);

//! Grab from opengl part.
extern GLuint2 spawn_gpu_mesh_buffers();

void add_gpu_mesh(ecs_world_t *world, ecs_entity_t prefab)
{
    zoxel_set_component(world, prefab, MeshGPULink, { 0 });
}

void spawn_gpu_mesh(ecs_world_t *world, ecs_entity_t e)
{
    ecs_set(world, e, MeshGPULink, { spawn_gpu_mesh_buffers() });
}

ECS_DTOR(MeshGPULink, ptr,
{
    if (ptr->value.x != 0)
    {
        glDeleteBuffers(1, &ptr->value.x);
    }
    if (ptr->value.y != 0)
    {
        glDeleteBuffers(1, &ptr->value.y);
    }
})