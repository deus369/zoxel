ecs_entity_t prefab_terrain_chunk_octree;

unsigned char get_chunk_division(int3 camera_position, int3 chunk_position) {
    return int_max(int_abs(chunk_position.x - camera_position.x), int_abs(chunk_position.z - camera_position.z));
}

ecs_entity_t spawn_prefab_terrain_chunk_octree(ecs_world_t *world, int3 size) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_add_tag(e, TerrainChunk)
    #ifdef zoxel_transforms3D
        add_transform3Ds(world, e);
        zox_set(e, Scale1D, { 0.05f })
    #endif
    zox_set(e, MeshDirty, { 0 })
    zox_set(e, Brightness, { 1.4f })
    zox_set(e, EntityLinks, { 0, NULL })    // character and minivox links
    add_seed(world, e, 666);
    add_chunk_octree(world, e, size);
    add_generate_chunk(world, e);
    if (!headless) {
        zox_add(e, MeshIndicies)
        zox_add(e, MeshVertices)
        zox_add(e, MeshUVs)
        zox_add(e, MeshColorRGBs)
        zox_add(e, ColorsGPULink)
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
        add_gpu_uvs(world, e);
        add_gpu_texture(world, e);
    }
    ecs_defer_end(world);
    prefab_terrain_chunk_octree = e;
    return e;
}

ecs_entity_t spawn_terrain_chunk_octree(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t terrain, int3 chunk_position, float3 position, float scale) {
    ecs_defer_begin(world);
    ecs_entity_t e = spawn_terrain_chunk(world, prefab, chunk_position, position, scale);
    zox_name("terrain_chunk_octree")
    zox_set_only(e, RenderLod, { get_chunk_division(int3_zero, chunk_position) })
    zox_set_only(e, VoxLink, { terrain })
    spawn_gpu_colors(world, e);
    ecs_defer_end(world);
    return e;
}