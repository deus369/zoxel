// element will follow mouse position
void MouseElementSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ZeviceLink)
    zox_sys_in(Anchor)
    zox_sys_in(CanvasLink)
    zox_sys_out(PixelPosition)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(CanvasLink, canvasLink)
        zox_sys_i(ZeviceLink, zeviceLink)
        zox_sys_i(Anchor, anchor)
        zox_sys_o(PixelPosition, pixelPosition)
        if (!canvasLink->value) {
            continue;
        }
        if (!zeviceLink->value) {
            continue;
        }
        if (!zox_has(zeviceLink->value, ZevicePointerPosition)) {
            zox_log(" > mouse link invalid, needs pointer position: %s\n", zox_get_name(zeviceLink->value))
        }
        const int2 position = zox_get_value(zeviceLink->value, ZevicePointerPosition)
        // if (!mouse) continue;
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        pixelPosition->value = position;
        pixelPosition->value.x -= anchor->value.x * canvas_size.x;
        pixelPosition->value.y -= anchor->value.y * canvas_size.y;
    }
} zox_declare_system(MouseElementSystem)
