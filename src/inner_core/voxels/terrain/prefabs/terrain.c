ecs_entity_t prefab_terrain;
ecs_entity_t local_terrain;

ecs_entity_t spawn_prefab_terrain(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_terrain")
    zox_add_tag(e, TerrainWorld)
    zox_prefab_set(e, ChunkLinks, { NULL })
    zox_prefab_set(e, TilemapLink, { 0 })
    prefab_terrain = e;
#ifdef zoxel_debug_prefabs
    zox_log(" + spawn_prefab terrain [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_terrain(ecs_world_t *world, ecs_entity_t tilemap, float3 position, float scale) {
    zox_instance(prefab_terrain)
    zox_name("terrain")
    zox_set(e, Position3D, { position })
    zox_set(e, Scale1D, { scale })
    zox_set(e, TilemapLink, { tilemap })
    // did tilemap have a voxlink previously
    zox_prefab_set(tilemap, VoxLink, { e })    // link tilemap to terrain
    local_terrain = e;
#ifdef zoxel_debug_spawns
    zox_log(" + spawned terrain [%lu]\n", e)
#endif
    return e;
}
