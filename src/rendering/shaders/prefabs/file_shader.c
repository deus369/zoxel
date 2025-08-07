entity spawn_prefab_file_shader(ecs *world) {
    zox_prefab()
    zox_prefab_name("file_shader")
    zox_prefab_add(e, ShaderSource)
    return e;
}

entity spawn_file_shader(ecs *world, const entity prefab,  char* source) {
    zox_instance(prefab)
    zox_name("file_shader")
    // zox_log("source: %s", source)
    zox_set(e, ShaderSource, {
        .value = source,
        .length = strlen(source) + 1,
    })
    return e;
}