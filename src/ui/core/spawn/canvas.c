ecs_entity_t spawn_canvas(ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t camera,
    const int2 size,
    const float4 screen_to_canvas)
{
    zox_instance(prefab)
    zox_name("canvas")
    zox_set(e, PixelSize, { size })
    zox_set(e, CameraLink, { camera })
    zox_set(e, ScreenToCanvas, { screen_to_canvas })
    return e;
}