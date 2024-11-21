ecs_entity_t spawn_prefab_vox_file(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_vox_file")
    zox_add_tag(e, Vox)
    zox_prefab_add(e, ChunkSize)
    zox_prefab_add(e, ChunkOctree)
    zox_prefab_add(e, ColorRGBs)
    return e;
}

ecs_entity_t spawn_vox_file(ecs_world_t *world, const ecs_entity_t prefab, const vox_file *data) {
    zox_instance(prefab)
    set_vox_file(world, e, data);

    // todo: remove RenderDisabled and just use RenderLod?
    // i can disable these later with RenderDisabled;
    // zox_set(e, RenderDisabled, { 1 })
    zox_set(e, RenderLod, { 0 })
    zox_set(e, ChunkDirty, { chunk_dirty_state_lod_updated })
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
// ChunkDirty, RenderLod, ChunkNeighbors
