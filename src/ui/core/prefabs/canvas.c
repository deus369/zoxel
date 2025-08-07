entity spawn_prefab_canvas(ecs *world) {
    zox_prefab()
    zox_prefab_name("canvas")
    zox_add_tag(e, Canvas)
    zox_prefab_add(e, AppLink)
    zox_prefab_set(e, CameraLink, { 0 })
    zox_prefab_set(e, PixelSize, { int2_zero })
    zox_prefab_set(e, ScreenToCanvas, { float4_zero })
    zox_prefab_set(e, Children, { 0, NULL });
    zox_prefab_set(e, WindowToTop, { 0 })
    zox_prefab_set(e, WindowsLayers, { 0 })
    zox_prefab_set(e, WindowsCount, { 0 })
    return e;
}