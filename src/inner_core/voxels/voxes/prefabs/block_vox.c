ecs_entity_t spawn_prefab_block_vox(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_block_vox")
    zox_add_tag(e, BlockVox)
    zox_prefab_set(e, RenderLod, { 0 })
    // BlockLink to original voxel meta data
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    return e;
}

ecs_entity_t spawn_block_vox(ecs_world_t *world, const SpawnBlockVox *data) {
    zox_instance(data->prefab)
    zox_name("block_vox")
    zox_set(e, Position3D, { data->position_real })
    zox_set(e, RenderLod, { data->render_lod })
    set_vox_from_vox_file(world, e, data->vox);
    spawn_gpu_mesh(world, e);
    spawn_gpu_colors(world, e);
    return e;
}
