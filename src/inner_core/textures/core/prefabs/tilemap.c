ecs_entity_t prefab_tilemap;

ecs_entity_t spawn_prefab_tilemap(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_tilemap")
    zox_add_tag(e, Tilemap)
    zox_prefab_set(e, TilemapSize, { { 1, 1 } })
    zox_prefab_set(e, TextureLinks, { 0, NULL })
    zox_prefab_set(e, TilemapUVs, { 0, NULL })
    add_texture(world, e, int2_zero, 1);
    if (!headless) {
        add_gpu_texture(world, e);
        add_gpu_material(world, e);
        add_gpu_texture(world, e);
    }
    prefab_tilemap = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab tilemap [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_tilemap(ecs_world_t *world) {
    zox_instance(prefab_tilemap)
    zox_name("tilemap")
    // zox_set(e, TextureSize, { texture_size })
    if (!headless) {
        spawn_gpu_material(world, e, get_shader3D_textured_value(world));
        spawn_gpu_texture(world, e);
    }
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned tilemap [%lu]\n", (long int) e);
    #endif
    // zox_log("   > spawned tilemap [%lu]\n", e)
    return e;
}