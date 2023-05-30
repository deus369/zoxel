ecs_entity_t ui_entities[256];  // a quick & dirty lookup for uis
int ui_entities_count = 0;

float2 get_ui_real_position2D(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 local_pixel_position, float2 anchor, int2 canvas_size) {
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvasSizef.x / canvasSizef.y;
    float2 position2D;
    if (parent == main_canvas) {
        position2D = (float2) { ((local_pixel_position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspect_ratio,
            ((local_pixel_position.y  / canvasSizef.y) - 0.5f + anchor.y) };
        #ifdef debug_ui_positioning
            zoxel_log("-> (main_canvas) Position2D : %fx%f\n", position2D.x, position2D.y);
        #endif
    } else {
        const Position2D *parent_position2D = ecs_get(world, parent, Position2D);
        const PixelSize *parent_pixel_size = ecs_get(world, parent, PixelSize);
        if (parent_position2D != NULL) position2D = parent_position2D->value;
        position2D = float2_add(position2D, (float2) { (local_pixel_position.x  / canvasSizef.x) * aspect_ratio,
            (local_pixel_position.y  / canvasSizef.y)});
        if (parent_pixel_size != NULL) {
            float2 parent_pixel_ratio = (float2) { parent_pixel_size->value.x / canvasSizef.y,
                parent_pixel_size->value.y / canvasSizef.y };
            position2D = float2_add(position2D, (float2) { - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x,
                - (parent_pixel_ratio.y / 2.0f) + parent_pixel_ratio.y * anchor.y });
        }
        #ifdef debug_ui_positioning
            zoxel_log("-> (parent) Position2D : %fx%f\n", position2D.x, position2D.y);
        #endif
    }
    return position2D;
}

float2 get_ui_real_position2D_canvas(int2 local_pixel_position, float2 anchor, float2 canvas_size_f, float aspect_ratio) {
    return (float2) { ((local_pixel_position.x  / canvas_size_f.x) - 0.5f + anchor.x) * aspect_ratio,
        ((local_pixel_position.y  / canvas_size_f.y) - 0.5f + anchor.y) };
}

float2 get_ui_real_position2D_parent(int2 local_pixel_position, float2 anchor, float2 parent_position2D,
    int2 parent_pixel_size, float2 canvas_size_f, float aspect_ratio) {
    float2 position2D = parent_position2D;
    position2D = float2_add(position2D, (float2) { (local_pixel_position.x  / canvas_size_f.x) * aspect_ratio,
        (local_pixel_position.y  / canvas_size_f.y)});
    float2 parent_pixel_ratio = (float2) { parent_pixel_size.x / canvas_size_f.y,
        parent_pixel_size.y / canvas_size_f.y };
    position2D = float2_add(position2D, (float2) { - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x,
        - (parent_pixel_ratio.y / 2.0f) + parent_pixel_ratio.y * anchor.y });
    #ifdef debug_ui_positioning
        zoxel_log("-> (parent) Position2D : %fx%f\n", position2D.x, position2D.y);
    #endif
    return position2D;
}

float2 initialize_ui_components(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, int2 local_pixel_position,
    int2 pixel_size, float2 anchor, unsigned char layer, int2 canvas_size) {
    if (parent == main_canvas) {
        ui_entities[ui_entities_count] = e;
        ui_entities_count++;
    }
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvasSizef.x / canvasSizef.y;
    float2 position2D = get_ui_real_position2D(world, e, parent, local_pixel_position, anchor, canvas_size);
    int2 global_pixel_position = (int2) { ceil(((position2D.x / aspect_ratio) + 0.5f) * canvasSizef.x),
        ((position2D.y + 0.5f) * canvasSizef.y) };
    zox_set_only(e, Anchor, { anchor })
    zox_set_only(e, PixelPosition, { local_pixel_position })
    zox_set_only(e, PixelSize, { pixel_size })
    zox_set_only(e, TextureSize, { pixel_size })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, ParentLink, { parent })
    zox_set_only(e, Layer2D, { layer })
    zox_set_only(e, Position2D, { position2D })
    zox_set_only(e, CanvasPixelPosition, { global_pixel_position })
    return position2D;
}

float2 initialize_ui_components_2(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 local_pixel_position, int2 pixel_size, float2 anchor, unsigned char layer,
    float2 parent_position, int2 parent_pixel_size, int2 canvas_size) {
    if (parent == main_canvas) {
        ui_entities[ui_entities_count] = e;
        ui_entities_count++;
    }
    // set scale
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    float2 position2D = get_ui_real_position2D_parent(local_pixel_position, anchor,
        parent_position, parent_pixel_size, canvas_size_f, aspect_ratio);
    int2 global_pixel_position = (int2) { ceil(((position2D.x / aspect_ratio) + 0.5f) * canvas_size_f.x),
        ((position2D.y + 0.5f) * canvas_size_f.y) };
    zox_set_only(e, Anchor, { anchor })
    zox_set_only(e, PixelSize, { pixel_size })
    zox_set_only(e, TextureSize, { pixel_size })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, ParentLink, { parent })
    zox_set_only(e, Layer2D, { layer })
    zox_set_only(e, PixelPosition, { local_pixel_position })
    zox_set_only(e, Position2D, { position2D })
    zox_set_only(e, CanvasPixelPosition, { global_pixel_position })
    return position2D;
}

// set children position as well
void set_ui_transform(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, unsigned char layer, int2 canvas_size) {
    #ifdef debug_ui_scaling
        zoxel_log("    - layer [%i] Repositioning entity [%lu]\n", layer, (long int) e);
    #endif
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvasSizef.x / canvasSizef.y;
    unsigned char is_valid = ecs_is_valid(world, e);
    if (is_valid && zox_has(e, PixelPosition)) {
        const PixelPosition *pixelPosition = ecs_get(world, e, PixelPosition);
        const Anchor *anchor = ecs_get(world, e, Anchor);
        int2 position = pixelPosition->value;
        float2 position2D = get_ui_real_position2D(world, e, parent, position, anchor->value, canvas_size);
        int2 global_pixel_position = (int2) { ceil((position2D.x / aspect_ratio + 0.5f) * canvasSizef.x),
            ((position2D.y + 0.5f) * canvasSizef.y) };
        zox_set_only(e, Position2D, { position2D })
        zox_set_only(e, CanvasPixelPosition, { global_pixel_position })
        #ifdef debug_ui_scaling
            zoxel_log("        -> to [%ix%i]\n", global_pixel_position.x, global_pixel_position.y);
        #endif
    } else {
        zoxel_log(" ! set_ui_transform - ui PixelPosition not found [%lu]\n", (long int) e);
    }
    //! Resize (if visible)
    if (!headless && is_valid && zox_has(e, MeshVertices2D)) {
        const PixelSize *pixelSize = ecs_get(world, e, PixelSize);
        float2 scaledSize2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_world_scale2D(world, e, square_vertices, 4, scaledSize2D);  // scale the mesh
        zox_set_only(e, MeshDirty, { 1 })
        #ifdef debug_ui_scaling
            zoxel_log("        -> Scaling: [%fx%f]\n", scaledSize2D.x, scaledSize2D.y);
        #endif
    }
    if (is_valid && zox_has(e, Children)) {
        layer++;
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++) {
            ecs_entity_t child = children->value[i];
            set_ui_transform(world, child, e, layer, canvas_size);
        }
    }
}

//! Reposition uis after viewport resizes.
void uis_on_viewport_resized(ecs_world_t *world, int2 screen_size) {
    zox_set_only(main_canvas, PixelSize, { screen_size })
    for (int i = 0; i < ui_entities_count; i++) {
        ecs_entity_t e = ui_entities[i];
        set_ui_transform(world, e, main_canvas, 0, screen_size);
        #ifdef debug_viewport_resize
            zoxel_log("    e [%i] - [%lu]\n", i, (long int) e);
        #endif
    }
    #ifdef debug_viewport_resize
        zoxel_log(" > viewport resized to dimensions: [%ix%i]\n", screen_size.x, screen_size.y);
    #endif
}

void toggle_ui(ecs_world_t *world, ecs_entity_t *e, ecs_entity_t (*spawn_ui)(ecs_world_t*, ecs_entity_t)) {
    if (*e == 0) {
        ecs_entity_t e2 = (*spawn_ui)(world, main_canvas);
        *e = e2;
    } else {
        zox_delete(*e)
        *e = 0;
    }
}

// if player device mode is gamepad, select pause ui
extern ecs_entity_t main_player;
extern void raycaster_select_ui_mut(ecs_world_t *world, ecs_entity_t raycaster_entity, ecs_entity_t ui_entity);

void select_first_button(ecs_world_t *world, ecs_entity_t first_button) {
    const DeviceMode *deviceMode = ecs_get(world, main_player, DeviceMode);
    if (deviceMode->value == zox_device_mode_gamepad) {
        zoxel_log(" > selecting first pause ui button [%lu]\n", first_button);
        raycaster_select_ui_mut(world, main_player, first_button);
    }
}