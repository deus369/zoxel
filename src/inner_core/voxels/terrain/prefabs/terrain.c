ecs_entity_t prefab_terrain;
ecs_entity_t local_terrain;

ecs_entity_t spawn_prefab_terrain(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_terrain")
    zox_add_tag(e, TerrainWorld)
    zox_add(e, ChunkLinks)
    zox_set(e, TilemapLink, { 0 })
    ecs_defer_end(world);
    prefab_terrain = e;
    return e;
}

ecs_entity_t spawn_terrain(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t tilemap, float3 position, float scale) {
    zox_instance(prefab)
    zox_name("terrain")
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, Scale1D, { scale })
    zox_set_only(e, TilemapLink, { tilemap })
    zox_set(tilemap, VoxLink, { e })    // link tilemap to vox?
    local_terrain = e;
    return e;
}