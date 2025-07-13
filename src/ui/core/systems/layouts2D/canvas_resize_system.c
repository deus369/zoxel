// todo: get dimensions off app using AppLink from Canvas, check it's dimensions
void CanvasResizeSystem(ecs_iter_t *it) {
    const int2 new_size = viewport_dimensions;
    zox_field_world()
    zox_field_in(CameraLink, cameraLinks, 1)
    zox_field_in(Children, childrens, 2)
    zox_field_in(ScreenToCanvas, screenToCanvass, 3)
    zox_field_out(PixelSize, pixelSizes, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        if (!cameraLink->value) continue;
        zox_field_i(ScreenToCanvas, screenToCanvass, screenToCanvas)
        zox_field_o(PixelSize, pixelSizes, pixelSize)
        const int2 canvas_size = screen_to_canvas_size(new_size, screenToCanvas->value);
        if (int2_equals(canvas_size, pixelSize->value)) continue;
        pixelSize->value = canvas_size;
        zox_field_e()
        zox_field_i(Children, childrens, children)
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t child = children->value[j];
            if (!zox_valid(child)) continue;
            // zox_log("  - [%i] canvas child is resizing: %lu\n", j, child)
            set_ui_transform(world, e, child, canvas_size, int2_half(canvas_size), canvas_size);
        }
    }
} zox_declare_system(CanvasResizeSystem)
