ecs_entity_t prefab_material;

ecs_entity_t spawn_prefab_material(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_material")
    zox_add_tag(e, Material)
    // zox_add(e, ShaderGPULink)
    add_gpu_material(world, e);
    prefab_material = e;
    return e;
}

ecs_entity_t spawn_material(ecs_world_t *world, ecs_entity_t shader) {
    zox_instance(prefab_material)
    zox_name("material")
    zox_set(e, ShaderLink, { shader })
    GLuint2 shader_value = zox_get_value(shader, ShaderGPULink)
    spawn_gpu_material(world, e, shader_value);
    return e;
}

void restore_material(ecs_world_t *world, ecs_entity_t e, GLuint2 shader) {
    spawn_gpu_material(world, e, shader);
}
