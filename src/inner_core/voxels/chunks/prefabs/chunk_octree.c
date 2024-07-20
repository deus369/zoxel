ecs_entity_t spawn_prefab_chunk_octree(ecs_world_t *world) {
    zox_prefab()
    // Voxels
    // todo: calculate this based on max LOD resolution (2 to power of resolution)
    const unsigned char max_length = 32; // todo: Calculate this from max resolution!
    const int3 size = (int3) { max_length, max_length, max_length };
    add_chunk_octree(world, e, size);
    zox_prefab_set(e, VoxScale, { default_vox_scale })
    // Transforms
    add_transform3Ds(world, e, 0);
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    // Rendering
    zox_prefab_set(e, Brightness, { 1.0f })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, MeshDirty, { 0 })
    prefab_add_mesh_basic(world, e);
    return e;
}
