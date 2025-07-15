extern uint spawn_gpu_material_program(const uint2 shader);

zox_component(MaterialGPULink, uint)
zox_component(MaterialInstancedGPULink, uint)

void add_gpu_material(ecs_world_t *world, const ecs_entity_t e) {
    if (!headless) {
        zox_prefab_set(e, MaterialGPULink, { 0 })
        zox_prefab_set(e, ShaderLink, { 0 })
    }
}

uint spawn_gpu_material(ecs_world_t *world,
    const ecs_entity_t e,
    const uint2 shader)
{
    uint gpu_material = 0;
    if (!headless) {
        gpu_material = spawn_gpu_material_program(shader);
        if (!gpu_material) {
            zox_log_error("spawn_gpu_material failed to initialize")
        } else {
            zox_set(e, MaterialGPULink, { gpu_material })
        }
    }
    return gpu_material;
}

ECS_DTOR(MaterialGPULink, ptr, {
    if (ptr->value != 0) {
        glDeleteProgram(ptr->value);
    }
})

/*uint get_material_value(ecs_world_t *world, ecs_entity_t material) /{
    return zox_get_value(material, MaterialGPULink)
}*/

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
