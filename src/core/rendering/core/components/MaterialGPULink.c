//! Contains a link to the MaterialGPULink on the GPU.
/**
*   Materials are shader program instances.
*   \todo Seperate mesh data into different files.
*/
zoxel_component(MaterialGPULink, GLuint);

//! Grab from opengl part.
extern GLuint spawn_gpu_material_program(const GLuint2 shader);

void add_gpu_material(ecs_world_t *world, ecs_entity_t prefab)
{
    zoxel_set_component(world, prefab, MaterialGPULink, { 0 });
}

void spawn_gpu_material(ecs_world_t *world, ecs_entity_t e, const GLuint2 shader)
{
    ecs_set(world, e, MaterialGPULink, { spawn_gpu_material_program(shader) });
}

ECS_DTOR(MaterialGPULink, ptr,
{
    // printf("ECS_DTOR MaterialGPULink [%i] on GPU.\n", ptr->value);
    if (ptr->value != 0)
    {
        glDeleteProgram(ptr->value);
    }
})

/*
ECS_CTOR(MaterialGPULink, ptr,
{
    // printf("ECS_CTOR MaterialGPULink!\n");
    ptr->value = 0;
})

ECS_MOVE(MaterialGPULink, dst, src,
{
    // printf("ECS_MOVE MaterialGPULink [%i] - [%i].\n", dst->value, src->value);
    if (dst->value)
    {
        glDeleteProgram(dst->value);
    }
    dst->value = src->value;
    src->value = 0;
})*/