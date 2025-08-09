entity spawn_prefab_block_vox_instanced(
    ecs *world,
    const entity prefab
) {
    zox_prefab_child(prefab)
    // add block stuff onto our vox instanced
    zox_prefab_name("block_vox_instanced")
    zox_prefab_set(e, BlockIndex, { 0 })
    zox_prefab_set(e, Color, {{ 25, 255, 25, 255 }})
    zox_prefab_set(e, RenderLodDirty, { zox_dirty_trigger })
    // testing
    prefab_add_cube_lines(world, e, color_white, 0);
    // zox_prefab_set(e, RenderDisabled, { 0 })
    // zox_prefab_set(e, InstanceLink, { 0 })
    // zox_prefab_set(e, VoxScale, { vox_model_scale })
    // zox_prefab_set(e, Bounds3D, { (float3) { 0.25f, 0.25f, 0.25f } })
    return e;
}

entity spawn_block_vox_instanced(
    ecs *world,
    const SpawnBlockVox *data
) {
    zox_instance(data->prefab)
    zox_name("block_vox_instanced")
    zox_set(e, BlockIndex, { data->block_index })
    zox_set(e, Position3D, { data->position_real })
    zox_set(e, VoxScale, { data->scale })
    zox_set(e, TransformMatrix, { float4x4_position(data->position_real) })
    zox_set(e, RenderLod, { data->render_lod })
    zox_set(e, RenderDisabled, { data->render_disabled })
    // set a random one if contains variants
    if (zox_valid(data->vox)) {
        if (zox_has(data->vox, ModelLinks)) {
            // zox_log("+ model group detected [%s]", zox_get_name(data->vox))
            zox_geter(data->vox, ModelLinks, models)
            if (models->length) {
                // srand - pick the model randomly, off our position in world
                srand(data->position_real.x * data->position_real.z * data->position_real.y);
                const entity model = models->value[rand() % (models->length)];
                zox_set(e, ModelLink, { model })
                // zox_log("   + picked [%s]", zox_get_name(model))
            }
        } else {
            zox_set(e, ModelLink, { data->vox })
        }
    }
    return e;
}
