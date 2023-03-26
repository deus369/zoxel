ecs_entity_t prefab_terrain;

ecs_entity_t spawn_prefab_terrain(ecs_world_t *world) {
    // int2 texture_size = { 16, 16 };
    ecs_defer_begin(world);
    // ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    ecs_entity_t e = ecs_new_prefab(world, "");
    // ecs_entity_t e = ecs_new(world, 0, voxel_prefab, 1);
    // ecs_add_id(world, e, EcsPrefab);
    // set_unique_entity_name(world, e, "prefab_terrain_chunk");
    // ecs_set_name(world, e, "prefab_terrain_chunk");
    zoxel_add_tag(world, e, TerrainWorld)
    zoxel_add(world, e, ChunkLinks)
    ecs_defer_end(world);
    prefab_terrain = e;
    return e;
}

ecs_entity_t spawn_terrain(ecs_world_t *world, ecs_entity_t prefab, float3 position, float scale) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    set_unique_entity_name(world, e, "terrain");
    ecs_set(world, e, Position3D, { position });
    ecs_set(world, e, Scale1D, { scale });
    ecs_defer_end(world);
    return e;
}