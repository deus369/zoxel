ecs_entity_t prefab_material;
// todo: keep a reference to the script for the material

ecs_entity_t spawn_prefab_material(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_material")
    zox_add_tag(e, Material)
    // zox_add(e, ShaderGPULink)
    add_gpu_material(world, e);
    prefab_material = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab material [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_material(ecs_world_t *world, GLuint2 shader) {
    zox_instance(prefab_material)
    zox_name("material")
    spawn_gpu_material(world, e, shader);
    return e;
}

void restore_material(ecs_world_t *world, ecs_entity_t e, GLuint2 shader) {
    spawn_gpu_material(world, e, shader);
}