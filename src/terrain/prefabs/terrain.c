ecs_entity_t spawn_prefab_terrain(ecs_world_t *world) {
    zox_prefab();
    zox_prefab_name("terrain");
    zox_add_tag(e, TerrainWorld);
    zox_prefab_set(e, StreamEndEvent, { NULL });
    zox_prefab_set(e, EventInput, { 0 });
    zox_prefab_set(e, ChunkLinks, { NULL });
    zox_prefab_set(e, TilemapLink, { 0 });
    zox_prefab_set(e, VoxScale, { default_vox_scale });
    zox_prefab_set(e, NodeDepth, { 0 });
#ifdef zox_is_flatlands
    zox_add_tag(e, FlatTerrain);
#endif
    return e;
}