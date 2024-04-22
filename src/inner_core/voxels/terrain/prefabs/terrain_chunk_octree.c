ecs_entity_t prefab_terrain_chunk_octree;

unsigned char get_chunk_division(int3 camera_position, int3 chunk_position) {
    return int_max(int_abs(chunk_position.x - camera_position.x), int_abs(chunk_position.z - camera_position.z));
}

void add_components_mesh_textured(ecs_world_t *world, ecs_entity_t e) {
    if (!headless) {
        zox_add(e, MeshIndicies)
        zox_add(e, MeshVertices)
        zox_add(e, MeshUVs)
        zox_add(e, MeshColorRGBs)
        add_gpu_mesh(world, e);
        // add_gpu_material(world, e);
        add_gpu_uvs(world, e);
        add_gpu_texture(world, e);
        add_gpu_colors(world, e);
    }
}

ecs_entity_t spawn_prefab_terrain_chunk_octree(ecs_world_t *world, int3 size) {
    zox_prefab()
    // zox_prefab_name("prefab_terrain_chunk_octree")
    add_seed(world, e, 666);
#ifdef zoxel_transforms3D
    add_transform3Ds(world, e);
    zox_set(e, Scale1D, { 0.5f })
#endif
#ifdef zoxel_rendering
    zox_prefab_set(e, MeshDirty, { 0 })
    zox_prefab_set(e, Brightness, { 1.0f })
    add_components_mesh_textured(world, e);
#endif
    // voxels_core
    add_chunk_octree(world, e, size);
    zox_add_tag(e, TerrainChunk)
    zox_add_tag(e, ChunkTextured)
    zox_prefab_set(e, EntityLinks, { 0, NULL })    // character and minivox links
    zox_prefab_set(e, GenerateChunk, { 1 }) // fails on samsungdwd
    prefab_terrain_chunk_octree = e;
    return e;
}

ecs_entity_t spawn_terrain_chunk_octree(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t terrain, int3 camera_position, int3 chunk_position, float3 position, float scale) {
    zox_instance(prefab)
    // zox_name("terrain_chunk_octree")
    zox_set(e, ChunkPosition, { chunk_position })
    zox_set(e, Position3D, { position })
    zox_set(e, Scale1D, { scale })
    zox_set(e, RenderLod, { get_chunk_division(camera_position, chunk_position) })
    zox_set(e, VoxLink, { terrain })
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_uvs(world, e);
        spawn_gpu_colors(world, e);
    }
    return e;
}
