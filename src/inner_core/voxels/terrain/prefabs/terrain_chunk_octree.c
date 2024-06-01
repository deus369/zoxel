ecs_entity_t spawn_prefab_terrain_chunk_octree(ecs_world_t *world, const int3 size) {
    zox_prefab()
    // zox_prefab_name("prefab_terrain_chunk_octree")
    add_seed(world, e, 666);
    add_transform3Ds(world, e, 0);
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, VoxScale, { 0.5f })
    zox_prefab_set(e, MeshDirty, { 0 })
    zox_prefab_set(e, Brightness, { 1.0f })
    zox_prefab_set(e, RenderDisabled, { 1 })
    zox_prefab_set(e, ChunkLodDirty, { 1 })
    // zox_prefab_set(e, GenerateChunkEntities, { 1 })
    add_components_mesh_textured(world, e);
    // voxels_core
    add_chunk_octree(world, e, size);
    zox_prefab_set(e, GenerateChunk, { 1 }) // fails on samsung phone?
    zox_prefab_set(e, ChunkSize, {{ 32, 32, 32 }})  // max resolution, should calculate this!
    zox_add_tag(e, TerrainChunk)
    zox_add_tag(e, ChunkTextured)
    zox_prefab_add(e, BlockSpawns)    // links to voxels in world
    zox_prefab_add(e, EntityLinks)    // character and minivox links
    // todo: calculate this based on max LOD resolution (2 to power of resolution)
#ifdef zox_disable_frustum_culling
    zox_set(e, RenderDisabled, { 0 })
#endif
    return e;
}

ecs_entity_t spawn_terrain_chunk_octree(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t terrain, const int3 camera_position, const int3 chunk_position, const float3 position) {
    zox_instance(prefab)
    // zox_name("terrain_chunk_octree")
    zox_set(e, ChunkPosition, { chunk_position })
    zox_set(e, Position3D, { position })
    zox_set(e, RenderLod, { get_camera_chunk_distance(camera_position, chunk_position) })
    zox_set(e, VoxLink, { terrain })
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_uvs(world, e);
        spawn_gpu_colors(world, e);
    }
    return e;
}
