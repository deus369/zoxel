ecs_entity_t spawn_prefab_terrain(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_terrain")
    zox_add_tag(e, TerrainWorld)
    // zox_prefab_set(e, StreamDirty, { 0 })
    zox_prefab_set(e, StreamEndEvent, { NULL })
    zox_prefab_set(e, EventInput, { 0 })
    zox_prefab_set(e, ChunkLinks, { NULL })
    zox_prefab_set(e, TilemapLink, { 0 })
#ifdef zox_is_flatlands
    zox_add_tag(e, FlatTerrain)
#endif
    return e;
}

ecs_entity_t spawn_terrain(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t tilemap, const float3 position, const float scale) {
    zox_instance(prefab)
    zox_name("terrain")
    zox_set(e, Position3D, { position })
    // zox_set(e, Scale1D, { scale })
    if (tilemap) {
        zox_set(e, TilemapLink, { tilemap })
        // did tilemap have a voxlink previously
        zox_prefab_set(tilemap, VoxLink, { e })    // link tilemap to terrain
    }
    local_terrain = e;
    return e;
}
