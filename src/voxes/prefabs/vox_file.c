entity spawn_prefab_vox_file(
    ecs *world,
    const entity prefab
) {
    zox_prefab_child(prefab)
    zox_prefab_name("vox_file")
    zox_add_tag(e, Vox)
    zox_prefab_add(e, ChunkSize)
    zox_prefab_add(e, VoxelNode)
    zox_prefab_set(e, ColorRGBs, { 0, NULL });
    zox_prefab_add(e, UboGPULink)
    // extra for rendering
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    // Transforms
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, TransformMatrix, { float4x4_identity })
    // Rendering
    zox_prefab_set(e, Brightness, { 1.0f })
    zox_prefab_set(e, RenderDisabled, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    prefab_add_mesh_basic(world, e);
    add_components_mesh_colored(world, e);
    return e;
}
