// gets an entities canvas root by climbing the ranks
entity get_root_canvas(ecs *world, const entity e) {
    if (!e) return 0;
    if (zox_has(e, CanvasLink)) { // shortcut to canvas
        const entity canvas = zox_get_value(e, CanvasLink)
        if (canvas) return canvas;
    }
    if (zox_has(e, Canvas)) return e;
    else if (!zox_has(e, ParentLink)) return 0;
    else {
        const entity parent = zox_get_value(e, ParentLink)
        return get_root_canvas(world, parent);
    }
}

// using this for render culling
entity get_root_canvas_camera(ecs *world, const entity e) {
    const entity canvas = get_root_canvas(world, e);
    if (!canvas || !zox_has(canvas, CameraLink)) return 0;
    else return zox_get_value(canvas, CameraLink)
}

