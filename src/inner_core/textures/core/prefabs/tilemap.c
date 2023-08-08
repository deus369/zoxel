ecs_entity_t prefab_tilemap;

ecs_entity_t spawn_prefab_tilemap(ecs_world_t *world) {
    zox_prefab()
    zox_name("prefab_tilemap")
    zox_add_tag(e, Tilemap)
    zox_set(e, TilemapSize, {{ 1, 1 }})
    zox_set(e, TextureLinks, { 0, NULL })
    zox_set(e, TilemapUVs, { 0, NULL })
    add_texture(world, e, int2_zero, 1);
    add_gpu_texture(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    prefab_tilemap = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab tilemap [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_tilemap(ecs_world_t *world) {
    zox_instance(prefab_tilemap)
    zox_name("tilemap")
    // zox_set_only(e, TextureSize, { texture_size })
    uint gpu_material = spawn_gpu_material(world, e, shader3D_textured);
    spawn_attributes_textured3D(gpu_material);
    spawn_gpu_texture(world, e);
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned tilemap [%lu]\n", (long int) e);
    #endif
    return e;
}