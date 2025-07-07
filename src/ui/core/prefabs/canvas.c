ecs_entity_t spawn_prefab_canvas(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_canvas")
    zox_add_tag(e, Canvas)
    zox_prefab_set(e, PixelSize, { int2_zero })
    zox_prefab_set(e, CameraLink, { 0 })
    zox_prefab_set(e, ScreenToCanvas, { float4_zero })
    zox_prefab_set(e, WindowToTop, { 0 })
    zox_prefab_set(e, WindowsLayers, { 0 })
    zox_prefab_set(e, WindowsCount, { 0 })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_canvas(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t camera, const int2 size, const float4 screen_to_canvas) {
    zox_instance(prefab)
    zox_name("canvas")
    zox_set(e, PixelSize, { size })
    zox_set(e, CameraLink, { camera })
    zox_set(e, ScreenToCanvas, { screen_to_canvas })
    return e;
}