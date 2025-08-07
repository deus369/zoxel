entity spawn_canvas(ecs *world,
    const entity prefab,
    const entity camera,
    const int2 size,
    const float4 screen_to_canvas,
    const entity app)
{
    zox_instance(prefab)
    zox_name("canvas")
    zox_set(e, PixelSize, { size })
    zox_set(e, CameraLink, { camera })
    zox_set(e, ScreenToCanvas, { screen_to_canvas })
    zox_set(e, AppLink, { app })
    return e;
}