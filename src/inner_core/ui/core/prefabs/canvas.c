// gets an entities canvas root by climbing the ranks
ecs_entity_t get_root_canvas(ecs_world_t *world, const ecs_entity_t e) {
    if (!e) return 0;
    if (zox_has(e, CanvasLink)) { // shortcut to canvas
        const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
        if (canvas) return canvas;
    }
    if (zox_has(e, Canvas)) return e;
    else if (!zox_has(e, ParentLink)) return 0;
    else {
        const ecs_entity_t parent = zox_get_value(e, ParentLink)
        return get_root_canvas(world, parent);
    }
}

// using this for render culling
ecs_entity_t get_root_canvas_camera(ecs_world_t *world, const ecs_entity_t e) {
    const ecs_entity_t canvas = get_root_canvas(world, e);
    if (!canvas || !zox_has(canvas, CameraLink)) return 0;
    else return zox_get_value(canvas, CameraLink)
}

ecs_entity_t spawn_prefab_canvas(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_canvas")
    zox_add_tag(e, Canvas)
    zox_prefab_set(e, PixelSize, { int2_zero })
    zox_prefab_set(e, Children, { 0, NULL })
    zox_prefab_set(e, CameraLink, { 0 })
    zox_prefab_set(e, ScreenToCanvas, { float4_zero })
    zox_prefab_set(e, WindowToTop, { 0 })
    zox_prefab_set(e, WindowsLayers, { 0 })
    zox_prefab_set(e, WindowsCount, { 0 })
    prefab_canvas = e;
    return e;
}

ecs_entity_t spawn_canvas(ecs_world_t *world, const ecs_entity_t camera, const int2 size, const float4 screen_to_canvas) {
    zox_instance(prefab_canvas)
    zox_name("canvas")
    zox_set(e, PixelSize, { size })
    zox_set(e, CameraLink, { camera })
    zox_set(e, ScreenToCanvas, { screen_to_canvas })
    return e;
}
