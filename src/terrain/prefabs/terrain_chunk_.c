/*ecs_entity_t spawn_prefab_terrain_chunk(ecs_world_t *world, int3 size) {
    zox_prefab_child(prefab_chunk)
    zox_prefab_name("prefab_terrain_chunk")
    zox_prefab_set(e, ChunkSize, { size })
    zox_add_tag(e, TerrainChunk)
    if (!headless) {
        zox_add(e, MeshUVs)
        add_gpu_uvs(world, e);
    }
    return e;
}

ecs_entity_t spawn_chunk_terrain(ecs_world_t *world, ecs_entity_t prefab, int3 chunk_position, float3 position, float scale) {
    zox_instance(prefab)
    // zox_name("terrain_chunk")
    zox_set(e, ChunkPosition, { chunk_position })
    zox_set(e, Position3D, { position })
    // zox_set(e, Scale1D, { scale })
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_uvs(world, e);
    }
    return e;
}
*/
