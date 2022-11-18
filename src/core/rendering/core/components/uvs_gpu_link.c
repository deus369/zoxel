//! Contains a link to the MaterialGPULink on the GPU.
/**
*   Materials are shader program instances.
*   \todo Seperate mesh data into different files.
*/
zoxel_component(UvsGPULink, GLuint);

void add_gpu_uvs(ecs_world_t *world, ecs_entity_t prefab)
{
    zoxel_set(world, prefab, UvsGPULink, { 0 });
}

//! Grab from opengl part.
extern GLuint2 spawn_gpu_mesh_buffers();
void spawn_gpu_uvs(ecs_world_t *world, ecs_entity_t e)
{
    GLuint buffers = spawn_gpu_uvs_buffers();
    ecs_set(world, e, UvsGPULink, { buffers });
}

ECS_DTOR(UvsGPULink, ptr,
{
    if (ptr->value != 0)
    {
        glDeleteBuffers(1, &ptr->value);
        ptr->value = 0;
    }
})