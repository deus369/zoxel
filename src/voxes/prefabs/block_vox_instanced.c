ecs_entity_t spawn_prefab_block_vox_instanced(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("block_vox_instanced")
    zox_prefab_set(e, BlockIndex, { 0 })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, Color, {{ 25, 255, 25, 255 }})
    zox_prefab_set(e, InstanceLink, { 0 })
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    zox_prefab_set(e, Bounds3D, { (float3) { 0.25f, 0.25f, 0.25f } })
    // testing
    prefab_add_cube_lines(world, e, color_white, 0);
    return e;
}

ecs_entity_t spawn_block_vox_instanced(ecs_world_t *world, const SpawnBlockVox *data) {
    zox_instance(data->prefab)
    zox_name("block_vox_instanced")
    zox_set(e, BlockIndex, { data->block_index })
    zox_set(e, Position3D, { data->position_real })
    zox_set(e, VoxScale, { data->scale })
    zox_set(e, TransformMatrix, { float4x4_position(data->position_real) })
    zox_set(e, RenderLod, { data->render_lod })
    zox_set(e, RenderDisabled, { data->render_disabled })
    return e;
}
