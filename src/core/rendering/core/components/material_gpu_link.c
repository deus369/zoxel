//! Contains a link to the MaterialGPULink on the GPU.
zoxel_component(MaterialGPULink, GLuint);

extern GLuint spawn_gpu_material_program(const GLuint2 shader);

void add_gpu_material(ecs_world_t *world, ecs_entity_t prefab) {
    if (!headless) {
        zoxel_set(world, prefab, MaterialGPULink, { 0 });
    }
}

void spawn_gpu_material(ecs_world_t *world, ecs_entity_t e, const GLuint2 shader) {
    if (!headless) {
        ecs_set(world, e, MaterialGPULink, { spawn_gpu_material_program(shader) });
    }
}

ECS_DTOR(MaterialGPULink, ptr, {
    if (ptr->value != 0) {
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