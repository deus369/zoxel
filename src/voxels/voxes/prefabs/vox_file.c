ecs_entity_t spawn_prefab_vox_file(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_vox_file")
    zox_add_tag(e, Vox)
    zox_prefab_add(e, ChunkSize)
    zox_prefab_add(e, ChunkOctree)
    zox_prefab_add(e, ColorRGBs)
    zox_prefab_add(e, UboGPULink)
    // extra for rendering
    const unsigned char max_length = 32; // todo: Calculate this from max resolution!
    const int3 size = (int3) { max_length, max_length, max_length };
    add_chunk_octree(world, e, size);
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    // Transforms
    add_transform3Ds(world, e, 0);
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    // Rendering
    zox_prefab_set(e, Brightness, { 1.0f })
    zox_prefab_set(e, RenderDisabled, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    prefab_add_mesh_basic(world, e);
    add_components_mesh_colored(world, e);

    return e;
}

ecs_entity_t spawn_vox_file(ecs_world_t *world, const ecs_entity_t prefab, const vox_file *data) {
    zox_instance(prefab)
    set_vox_file(world, e, data);

    // todo: remove RenderDisabled and just use RenderLod?
    // i can disable these later with RenderDisabled;
    // zox_set(e, RenderDisabled, { 1 })
    zox_set(e, RenderLod, { 0 })
    zox_set(e, ChunkMeshDirty, { chunk_dirty_state_trigger })
    zox_set(e, Scale1D, { 2 })
    zox_set(e, Position3D, { { 2 * (rand() % 6), 0, 2 * (rand() % 6) }})

#ifdef zox_disable_io_voxes
    zox_delete(e)
    return 0;
#endif
    return e;
}

// things for mesh generation:
// ChunkOctree, ColorRGBs, ChunkSize (used to centre, should be vox size?)
// MeshIndicies, MeshVertices, MeshColorRGBs, MeshDirty
// ChunkMeshDirty, RenderLod, ChunkNeighbors
