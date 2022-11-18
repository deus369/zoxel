//! Contains a link to the MaterialGPULink on the GPU.
/**
*   Materials are shader program instances.
*   \todo Seperate mesh data into different files.
*/

/*
zoxel_component(TextureCoordinatesGPULink, GLuint2);

//! Grab from opengl part.
// extern GLuint2 spawn_gpu_texture_coordinate_buffers();

void add_gpu_texture_coordinates(ecs_world_t *world, ecs_entity_t prefab)
{
    zoxel_set(world, prefab, TextureCoordinatesGPULink, { 0 });
}

void spawn_gpu_texture_coordinates(ecs_world_t *world, ecs_entity_t e)
{
    // ecs_set(world, e, TextureCoordinatesGPULink, { spawn_gpu_texture_coordinate_buffers() });
}

ECS_DTOR(TextureCoordinatesGPULink, ptr,
{
    if (ptr->value.x != 0)
    {
        glDeleteBuffers(1, &ptr->value.x);
    }
    if (ptr->value.y != 0)
    {
        glDeleteBuffers(1, &ptr->value.y);
    }
})*/