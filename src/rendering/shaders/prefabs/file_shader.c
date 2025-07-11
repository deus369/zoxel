ecs_entity_t spawn_prefab_file_shader(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("file_shader")
    zox_prefab_add(e, ShaderSource)
    return e;
}

ecs_entity_t spawn_file_shader(ecs_world_t *world, const ecs_entity_t prefab,  char* source) {
    zox_instance(prefab)
    zox_name("file_shader")
    // zox_log("source: %s", source)
    zox_set(e, ShaderSource, {
        .value = source,
        .length = strlen(source) + 1,
    })
    return e;
}