ecs_entity_t spawn_prefab_block_vox(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("block_vox")
    zox_add_tag(e, BlockVox)
    zox_prefab_set(e, CloneVox, { 0})
    zox_prefab_set(e, CloneVoxLink, { 0 })
    zox_prefab_set(e, ChunkLod, { 255 })
    zox_prefab_set(e, BlockIndex, { 0 })
    zox_prefab_set(e, RenderLod, { 255 })
    // BlockLink to original voxel meta data
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    // for debug
    zox_prefab_set(e, Bounds3D, { (float3) { 0.25f, 0.25f, 0.25f } })
    prefab_add_cube_lines(world, e, color_white, 0);
    return e;
}

ecs_entity_t spawn_block_vox(ecs_world_t *world,
    const SpawnBlockVox *data)
{
    zox_instance(data->prefab)
    zox_name("block_vox")
    // transforms
    zox_set(e, Position3D, { data->position_real })
    // zox_set(e, Scale1D, { data->scale })
    zox_set(e, VoxScale, { vox_model_scale }) // data->scale })
    // zox_set(e, TransformMatrix, { float4x4_position(data->position_real) })
    // zox_set(e, TransformMatrix, { float4x4_transform_scale(data->position_real, quaternion_identity, data->scale) })
    // rendering
    zox_set(e, RenderLod, { data->render_lod })
    zox_set(e, RenderDisabled, { data->render_disabled })
    // voxels
    zox_set(e, BlockIndex, { data->block_index })
    zox_set(e, CloneVox, { 1 })
    zox_set(e, CloneVoxLink, { data->vox })
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_colors(world, e);
    }
    // zox_log("+ spawned block vox with scale: %f", data->scale)
    return e;
}