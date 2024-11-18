// only used be lines atm
extern void resize_ui_line2D(ecs_world_t *world, ecs_entity_t e, int2 canvas_size);

float2 get_ui_real_position2D(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t parent, const int2 local_pixel_position, const float2 anchor, const int2 canvas_size) {
    const float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    const float aspect_ratio = canvasSizef.x / canvasSizef.y;
    float2 position2D;
    if (zox_has(parent, Canvas)) {
        position2D = (float2) { ((local_pixel_position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspect_ratio, ((local_pixel_position.y  / canvasSizef.y) - 0.5f + anchor.y) };
#ifdef debug_ui_positioning
        zox_log("-> Canvas Position2D : %fx%f\n", position2D.x, position2D.y)
#endif
    } else {
        const Position2D *parent_position2D = zox_get(parent, Position2D)
        const PixelSize *parent_pixel_size = zox_get(parent, PixelSize)
        if (parent_position2D != NULL) position2D = parent_position2D->value;
        position2D = float2_add(position2D, (float2) { (local_pixel_position.x  / canvasSizef.x) * aspect_ratio, (local_pixel_position.y  / canvasSizef.y)});
        if (parent_pixel_size != NULL) {
            const float2 parent_pixel_ratio = (float2) { parent_pixel_size->value.x / canvasSizef.y, parent_pixel_size->value.y / canvasSizef.y };
            position2D = float2_add(position2D, (float2) { - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x, - (parent_pixel_ratio.y / 2.0f) + parent_pixel_ratio.y * anchor.y });
        }
#ifdef debug_ui_positioning
        zox_log("-> (parent) Position2D : %fx%f\n", position2D.x, position2D.y)
#endif
    }
    return position2D;
}

// only used be lines atm
float2 get_ui_real_position2D_canvas(const int2 local_pixel_position, const float2 anchor, const float2 canvas_size_f, const float aspect_ratio) {
    return (float2) { ((local_pixel_position.x  / canvas_size_f.x) - 0.5f + anchor.x) * aspect_ratio, ((local_pixel_position.y  / canvas_size_f.y) - 0.5f + anchor.y) };
}

float2 get_ui_real_position2D_parent(const int2 local_pixel_position, const float2 anchor, const float2 parent_position2D, const int2 parent_pixel_size, const float2 canvas_size_f, const float aspect_ratio) {
    const float2 parent_pixel_ratio = (float2) { parent_pixel_size.x / canvas_size_f.y, parent_pixel_size.y / canvas_size_f.y };
    float2 position2D = parent_position2D;
    const float2 add_1 = (float2) { (local_pixel_position.x  / canvas_size_f.x) * aspect_ratio, (local_pixel_position.y  / canvas_size_f.y)};
    const float2 add_2 = (float2) { - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x, - (parent_pixel_ratio.y / 2.0f) + parent_pixel_ratio.y * anchor.y };
    float2_add_float2_p(&position2D, add_1);
    float2_add_float2_p(&position2D, add_2);
#ifdef debug_ui_positioning
    zox_log(" -> (parent) Position2D : %fx%f\n", position2D.x, position2D.y)
#endif
    return position2D;
}



int2 get_element_pixel_position_global(const int2 parent_pixel_position_global, const int2 parent_size, const int2 pixel_position, const float2 anchor) {
    int2 pixel_position_global = parent_pixel_position_global;
    // position is actually the centre point, so get the bottom left corner here
    pixel_position_global.x -= parent_size.x / 2;
    pixel_position_global.y -= parent_size.y / 2;
    // now centre it within the parent element / canvas
    pixel_position_global.x += (int) (parent_size.x * anchor.x);
    pixel_position_global.y += (int) (parent_size.y * anchor.y);
    // add local position offset
    pixel_position_global.x += pixel_position.x;
    pixel_position_global.y += pixel_position.y;
    return pixel_position_global;
}

float2 get_element_position(const int2 pixel_position_global, const int2 canvas_size) {
    const float2 canvas_size_f = int2_to_float2(canvas_size);
    const float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    float2 position = int2_to_float2(pixel_position_global);
    float2_divide_float2(&position, canvas_size_f);
    // (float2) { pixel_position_global.x * (aspect_ratio / canvas_size_f.x), pixel_position_global.y / canvas_size_f.y };
    // we get our 0 to 1, make -0.5 to 0.5, then stretch x along canvas
    position.x -= 0.5f;
    position.y -= 0.5f;
    position.x *= aspect_ratio;
    // zox_log("   > canvas_size [%fx%f] aspect_ratio [%f]\n", canvas_size_f.x, canvas_size_f.y, aspect_ratio)
    return position;
}

void on_element_parent_updated(ecs_world_t *world, const ecs_entity_t e, const int2 local_pixel_position, const float2 anchor, const float2 parent_position, const int2 parent_pixel_size, const float2 canvas_size_f) {
    const float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    const float2 position2D = get_ui_real_position2D_parent(local_pixel_position, anchor, parent_position, parent_pixel_size, canvas_size_f, aspect_ratio);
    const int2 global_pixel_position = (int2) { ceil(((position2D.x / aspect_ratio) + 0.5f) * canvas_size_f.x), ((position2D.y + 0.5f) * canvas_size_f.y) };
    zox_set(e, Position2D, { position2D })
    zox_set(e, CanvasPosition, { global_pixel_position })
}

void set_window_bounds_to_canvas(ecs_world_t *world, const ecs_entity_t e, const int2 canvas_size, const int2 window_size, const float2 anchor) {
    // note: can't actually use components in frame we spawn them
    const float2 anchor_reverse = (float2) { 1 - anchor.x, 1 - anchor.y };
    int4 drag_limits = (int4) { - canvas_size.x * anchor.x + window_size.x / 2, canvas_size.x * anchor_reverse.x - window_size.x / 2, - canvas_size.y * anchor.y + window_size.y / 2, canvas_size.y * anchor_reverse.y - window_size.y / 2 };
    zox_set(e, DraggableLimits, { drag_limits });
}

void limited_element(PixelPosition *pixel_position, const int4 drag_bounds) {
    if (pixel_position->value.x < drag_bounds.x) pixel_position->value.x = drag_bounds.x;
    if (pixel_position->value.x > drag_bounds.y) pixel_position->value.x = drag_bounds.y;
    if (pixel_position->value.y < drag_bounds.z) pixel_position->value.y = drag_bounds.z;
    if (pixel_position->value.y > drag_bounds.w) pixel_position->value.y = drag_bounds.w;
}

void limit_element(ecs_world_t *world, const ecs_entity_t e) {
    if (!zox_valid(e) || !zox_has(e, PixelPosition) || !zox_has(e, DraggableLimits)) return;
    PixelPosition *pixel_position = zox_get_mut(e, PixelPosition)
    const int4 drag_bounds = zox_get_value(e, DraggableLimits)
    limited_element(pixel_position, drag_bounds);
    zox_modified(e, PixelPosition)
}

extern void anchor_element_position2D(int2 *position, const float2 position_anchor, const int2 window_size);
extern void anchor_element_size2D(int2 *size, const float2 anchor, const int2 parent_size);

// called by CanvasResizeSystem
void set_ui_transform(ecs_world_t *world, const ecs_entity_t parent, const ecs_entity_t e, const int2 canvas_size, const int2 parent_position, const int2 parent_size) {
    if (!zox_valid(e)) return;
    const float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    int2 pixel_size = int2_zero;
    if (zox_has(e, AnchorSize)) {
        const float2 anchor_size = zox_get_value(e, AnchorSize)
        anchor_element_size2D(&pixel_size, anchor_size, parent_size);
        zox_set(e, PixelSize, { pixel_size })
    } else if (zox_has(e, PixelSize)) {
        pixel_size = zox_get_value(e, PixelSize)
    }
    if (zox_has(e, RenderTexture)) {
        set_render_texture_gpu(zox_gett_value(e, TextureGPULink), pixel_size);
    }
    if (!headless && zox_has(e, MeshVertices2D)) {
        const unsigned char mesh_alignment = zox_get_value(e, MeshAlignment)
        MeshVertices2D *meshVertices2D = zox_get_mut(e, MeshVertices2D)
        const float2 scale2D = (float2) { pixel_size.x / canvasSizef.y, pixel_size.y / canvasSizef.y };
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(mesh_alignment), 4, scale2D);
        zox_modified(e, MeshVertices2D)
        zox_set(e, MeshDirty, { mesh_state_trigger })
#ifdef debug_ui_scaling
        zox_log("        -> Scaling: [%fx%f]\n", scale2D.x, scale2D.y)
#endif
    }
    resize_ui_line2D(world, e, canvas_size);
    if (zox_has(e, BoundToCanvas)) {
        const float2 anchor = zox_get_value(e, Anchor)
        set_window_bounds_to_canvas(world, e, canvas_size, pixel_size, anchor);
    }
    limit_element(world, e); // check limited elements - bounded
    if (zox_has(e, PixelPosition)) {
        const float2 anchor = zox_get_value(e, Anchor)
        int2 pixel_position = zox_get_value(e, PixelPosition)
        // todo: make this more widespread, used atm just for game_ui
        const int2 position_in_canvas = get_element_pixel_position_global(parent_position, parent_size, pixel_position, anchor);
        const float2 position_real = get_element_position(position_in_canvas, canvas_size);
        anchor_element_position2D(&pixel_position, anchor, pixel_size);
        zox_set(e, Position2D, { position_real })
        zox_set(e, CanvasPosition, { position_in_canvas })
#ifdef debug_ui_scaling
        zox_log("        -> to [%ix%i]\n", position_in_canvas.x, position_in_canvas.y)
#endif
        if (zox_has(e, Children)) {
            const Children *children = zox_get(e, Children)
            for (int i = 0; i < children->length; i++) set_ui_transform(world, e, children->value[i], canvas_size, position_in_canvas, pixel_size);
        }
    }
}

void initialize_element_invisible(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t parent, const ecs_entity_t canvas, const int2 pixel_position, const int2 pixel_size, const float2 anchor, const unsigned char layer, const float2 position2D, const int2 pixel_position_global) {
    zox_set(e, Anchor, { anchor })
    zox_set(e, Layer2D, { layer })
    zox_set(e, PixelSize, { pixel_size })
    zox_set(e, PixelPosition, { pixel_position })
    zox_set(e, Position2D, { position2D }) // set this inside pixel position system
    zox_set(e, CanvasPosition, { pixel_position_global }) // set this inside system too
    zox_set(e, CanvasLink, { canvas })
    zox_set(e, ParentLink, { parent })
    if (canvas == parent) {
        on_child_added(world, canvas, e);
        zox_set(canvas, WindowToTop, { e })
    }
}

void initialize_element(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t parent, const ecs_entity_t canvas, const int2 pixel_position, const int2 pixel_size, const int2 texture_size, const float2 anchor, const unsigned char layer, const float2 position2D, const int2 pixel_position_global) {
    initialize_element_invisible(world, e, parent, canvas, pixel_position, pixel_size, anchor, layer, position2D, pixel_position_global);
    zox_set(e, TextureSize, { texture_size })
    // use a function that updates it, but keep seperate from initialize function which merely sets variables
}
