ecs_entity_t spawn_prefab_renderer_instance(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_renderer_instance")
    zox_add_tag(e, RendererInstance)
    // zox_prefab_set(e, ShaderSourceIndex, { 0 })
    // add_gpu_shader(world, e);
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, Scale1D, { 1 })
    zox_prefab_set(e, Brightness, { 1 })
    // zox_prefab_set(e, Color, {{ 25, 255, 25, 255 }})
    zox_prefab_set(e, RenderDisabled, { 0 })
    return e;
}
