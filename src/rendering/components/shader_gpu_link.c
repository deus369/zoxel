zox_component(ShaderGPULink, uint2)

void add_gpu_shader(ecs_world_t *world, const ecs_entity_t e) {
    if (!headless) zox_prefab_set(e, ShaderGPULink, { { 0, 0 } })
}

ECS_DTOR(ShaderGPULink, ptr, {
    // delete_shader(ptr->value); // why cant we do this
    if (ptr->value.x != 0) glDeleteShader(ptr->value.x);
    if (ptr->value.y != 0) glDeleteShader(ptr->value.y);
})

uint2 get_shader_value(ecs_world_t *world, const ecs_entity_t shader) {
    if (!zox_valid(shader)) return (uint2) { 0, 0 };
    return zox_get_value(shader, ShaderGPULink)
}
