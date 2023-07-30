extern uint spawn_gpu_material_program(const uint2 shader);

zox_component(MaterialGPULink, uint)
zox_component(MaterialInstancedGPULink, uint)

void add_gpu_material(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, MaterialGPULink, { 0 })
}

void add_gpu_instanced_material(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) zox_set(e, MaterialInstancedGPULink, { 0 })
}

void spawn_gpu_material(ecs_world_t *world, ecs_entity_t e, const uint2 shader) {
    if (!headless) zox_set_only(e, MaterialGPULink, { spawn_gpu_material_program(shader) })
}

ECS_DTOR(MaterialGPULink, ptr, {
    if (ptr->value != 0) glDeleteProgram(ptr->value);
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