ecs_entity_t spawn_prefab_render_texture(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)    // from element_basic
    zox_add_tag(e, RenderTexture)
    zox_add_tag(e, TextureRGB)
    zox_prefab_set(e, AnchorSize, { float2_one })
    zox_prefab_add(e, CameraLink)
    zox_set(e, TextureDirty, { 0 })
    // for now we must do this otherwise we get edge pixels
    const float scale1 = 1.01f;
    zox_set(e, Scale1D, { scale1 })
    // no 2D matrix system yet
    // zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, TransformMatrix, { float4x4_transform_scale(float3_zero, quaternion_identity, scale1) })
    return e;
}