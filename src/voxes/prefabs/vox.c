// todo: pre prefab functions?
extern void clone_vox_data(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t source, byte max_depth);

ecs_entity_t spawn_prefab_vox(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_vox")
    zox_add_tag(e, Vox)
    add_components_mesh_colored(world, e);
    // transform
    zox_prefab_set(e, Euler, { float3_zero })
    zox_prefab_set(e, Scale1D, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    zox_prefab_set(e, RenderDisabled, { 0 })
    // zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    // vox
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    zox_prefab_set(e, GenerateChunk, { 0 })
    //if (!headless) {
    //    zox_add_tag(e, RendererColored)
    //}
    return e;
}

ecs_entity_t spawn_vox(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t vox, const float3 position, const byte render_lod) {
    zox_instance(prefab)
    zox_set(e, Position3D, { position })
    zox_set(e, RenderLod, { render_lod })
    clone_vox_data(world, e, vox, max_octree_depth);
    spawn_gpu_colors(world, e);
    return e;
}

ecs_entity_t spawn_vox_basic(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    spawn_gpu_mesh(world, e);
    // spawn_gpu_uvs(world, e);
    spawn_gpu_colors(world, e);
    return e;
}