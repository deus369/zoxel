ecs_entity_t spawn_prefab_chunk(
    ecs_world_t *world,
    ecs_entity_t prefab
) {
    zox_prefab_child(prefab);
    zox_prefab_name("chunk");
    zox_prefab_set(e, VoxScale, { default_vox_scale });
    // Transforms
    zox_prefab_set(e, Position3D, { float3_zero });
    zox_prefab_set(e, Rotation3D, { float4_identity });
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    // Rendering
    zox_prefab_set(e, Brightness, { 1.0f });
    zox_prefab_set(e, RenderDisabled, { 0 });
    zox_prefab_set(e, MeshDirty, { 0 });
    prefab_add_mesh_basic(world, e);
    return e;
}