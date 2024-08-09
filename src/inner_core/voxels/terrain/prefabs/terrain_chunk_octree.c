ecs_entity_t spawn_prefab_terrain_chunk_octree(ecs_world_t *world, const ecs_entity_t prefab, const int3 size) {
    zox_prefab_child(prefab)
    add_components_mesh_textured(world, e);
    // Terrain / Generation
    zox_add_tag(e, TerrainChunk)
    zox_add_tag(e, ChunkTextured)
    add_seed(world, e, 666);
    zox_prefab_set(e, GenerateChunk, { 1 }) // fails on samsung phone?
    // links to sub chunk things - remember: these have to be set to NULL as not set in initialization
    zox_prefab_set(e, EntityLinks, { 0, NULL }) // character and minivox links
    // zox_prefab_set(e, BlockSpawns, { NULL })    // links to voxels in world
    zox_prefab_set(e, BlocksSpawned, { 0 })
#ifdef zox_is_flatlands
    zox_add_tag(e, FlatlandChunk)
#endif
#ifdef zox_disable_frustum_culling
    zox_set(e, RenderDisabled, { 0 })
#else
    zox_set(e, RenderDisabled, { 1 })
#endif
    zox_add_tag(e, ChunkDebugger)
    zox_set(e, RenderLod, { 255 }) // start hidden
    return e;
}

ecs_entity_t spawn_terrain_chunk_octree(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t terrain, const int3 camera_position, const int3 chunk_position, const float3 position) {
    zox_instance(prefab)
    zox_name("terrain_chunk")
    zox_set(e, ChunkPosition, { chunk_position })
    zox_set(e, Position3D, { position })
    // zox_set(e, RenderLod, { get_camera_chunk_distance(camera_position, chunk_position) })
    zox_set(e, VoxLink, { terrain })
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_uvs(world, e);
        spawn_gpu_colors(world, e);
    }
    return e;
}
