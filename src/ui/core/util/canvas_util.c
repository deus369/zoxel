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

