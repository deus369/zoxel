ecs_entity_t spawn_prefab_vox(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_vox")
    zox_add_tag(e, Vox)
    // transforms
    zox_prefab_set(e, Euler, { float3_zero })
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, Scale1D, { 1.0f })
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    // because we set the data on spawn, no need to generate here
    zox_prefab_set(e, GenerateChunk, { 0 })
    zox_prefab_set(e, ChunkDirty, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    zox_prefab_set(e, RenderDisabled, { 0 })
    add_chunk_colors(world, e);
    add_gpu_colors(world, e);
    return e;
}

ecs_entity_t spawn_vox(ecs_world_t *world, const ecs_entity_t prefab, const vox_file *vox, const float3 position, const unsigned char render_lod) {
    zox_instance(prefab)
    zox_prefab_set(e, Position3D, { position })
    zox_prefab_set(e, RenderLod, { render_lod })
    set_vox_from_vox_file(world, e, vox);
    spawn_gpu_colors(world, e);
    return e;
}
