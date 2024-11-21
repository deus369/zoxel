ecs_entity_t spawn_prefab_block_vox_instanced(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_block_vox_instanced")
    if (!headless) {
        zox_add_tag(e, InstanceRenderer)
    }
    zox_set(e, DestroyInTime, { 0 })
    //zox_add_tag(e, BlockVox)
    zox_prefab_set(e, BlockIndex, { 0 })
    zox_prefab_set(e, RenderLod, { 0 })
    zox_prefab_set(e, RenderDisabled, { 0 })
    // BlockLink to original voxel meta data
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, VoxScale, { vox_model_scale * 1 })
    // for debug
    zox_prefab_set(e, Bounds3D, { (float3) { 0.25f, 0.25f, 0.25f } })
    #ifdef zoxel_debug_bounds
    prefab_add_cube_lines(world, e, color_rgb_white, 1);
    #else
    prefab_add_cube_lines(world, e, color_rgb_white, 0);
    #endif
    return e;
}

ecs_entity_t spawn_block_vox_instanced(ecs_world_t *world, const SpawnBlockVox *data) {
    zox_instance(data->prefab)
    zox_name("block_vox_instanced")
    zox_set(e, BlockIndex, { data->block_index })
    zox_set(e, Position3D, { data->position_real })
    zox_set(e, RenderLod, { data->render_lod })
    // zox_set(e, RenderDisabled, { data->render_disabled })
    // zox_set(e, CloneVoxLink, { data->vox })
    // zox_log("pp-p")
    return e;
}
