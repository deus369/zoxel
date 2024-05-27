ecs_entity_t spawn_prefab_texture(ecs_world_t *world, const int2 texture_size) {
    zox_prefab()
    zox_prefab_name("prefab_texture")
    prefab_add_texture(world, e, texture_size);
    return e;
}

ecs_entity_t spawn_texture(ecs_world_t *world, const ecs_entity_t prefab, int2 size) {
    zox_instance(prefab)
    // zoxel_log(" > spawned texture data [%lu]\n", e);
    zox_set(e, TextureSize, { size })
    return e;
}
