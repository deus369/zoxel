// TransformMatrix, RenderDisabled, InstanceLink
ecs_entity_t spawn_prefab_vox_instanced(ecs_world_t *world,
    const ecs_entity_t prefab)
{
    zox_prefab_child(prefab)
    zox_prefab_name("vox_instanced")
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, RenderLod, { 0 })
    zox_prefab_set(e, RenderLodDirty, { zox_dirty_none })
    zox_prefab_set(e, InstanceLink, { 0 })
    zox_prefab_set(e, InstanceLinks, { 0,0,0,0,0,0,0,0 })
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    zox_prefab_set(e, Bounds3D, { (float3) { 0.25f, 0.25f, 0.25f } })
    // zox_prefab_set(e, Color, { { 25, 255, 25, 255 } })
    return e;
}

ecs_entity_t spawn_vox_instanced(ecs_world_t *world,
    const ecs_entity_t prefab,
    const float3 position,
    const byte render_disabled,
    const byte render_lod,
    const float vox_scale)
{
    zox_instance(prefab)
    zox_name("vox_instanced")
    zox_set(e, Position3D, { position })
    zox_set(e, TransformMatrix, { float4x4_position(position) })
    zox_set(e, RenderLod, { render_lod })
    zox_set(e, RenderDisabled, { render_disabled })
    zox_set(e, VoxScale, { vox_scale })
    return e;
}
