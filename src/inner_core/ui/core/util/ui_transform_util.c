float2 get_ui_real_position2D(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, int2 local_pixel_position, float2 anchor, int2 canvas_size) {
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvasSizef.x / canvasSizef.y;
    float2 position2D;
    if (parent == main_canvas) {
        position2D = (float2) { ((local_pixel_position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspect_ratio, ((local_pixel_position.y  / canvasSizef.y) - 0.5f + anchor.y) };
        #ifdef debug_ui_positioning
            zox_log("-> (main_canvas) Position2D : %fx%f\n", position2D.x, position2D.y)
        #endif
    } else {
        const Position2D *parent_position2D = zox_get(parent, Position2D)
        const PixelSize *parent_pixel_size = zox_get(parent, PixelSize)
        if (parent_position2D != NULL) position2D = parent_position2D->value;
        position2D = float2_add(position2D, (float2) { (local_pixel_position.x  / canvasSizef.x) * aspect_ratio, (local_pixel_position.y  / canvasSizef.y)});
        if (parent_pixel_size != NULL) {
            float2 parent_pixel_ratio = (float2) { parent_pixel_size->value.x / canvasSizef.y, parent_pixel_size->value.y / canvasSizef.y };
            position2D = float2_add(position2D, (float2) { - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x, - (parent_pixel_ratio.y / 2.0f) + parent_pixel_ratio.y * anchor.y });
        }
        #ifdef debug_ui_positioning
            zox_log("-> (parent) Position2D : %fx%f\n", position2D.x, position2D.y)
        #endif
    }
    return position2D;
}

float2 get_ui_real_position2D_canvas(int2 local_pixel_position, float2 anchor, float2 canvas_size_f, float aspect_ratio) {
    return (float2) { ((local_pixel_position.x  / canvas_size_f.x) - 0.5f + anchor.x) * aspect_ratio, ((local_pixel_position.y  / canvas_size_f.y) - 0.5f + anchor.y) };
}

float2 get_ui_real_position2D_parent(int2 local_pixel_position, float2 anchor, float2 parent_position2D, int2 parent_pixel_size, float2 canvas_size_f, float aspect_ratio) {
    float2 parent_pixel_ratio = (float2) { parent_pixel_size.x / canvas_size_f.y, parent_pixel_size.y / canvas_size_f.y };
    float2 position2D = parent_position2D;
    float2 add_1 = (float2) { (local_pixel_position.x  / canvas_size_f.x) * aspect_ratio, (local_pixel_position.y  / canvas_size_f.y)};
    float2 add_2 = (float2) { - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x, - (parent_pixel_ratio.y / 2.0f) + parent_pixel_ratio.y * anchor.y };
    float2_add_float2_p(&position2D, add_1);
    float2_add_float2_p(&position2D, add_2);
    #ifdef debug_ui_positioning
        zox_log(" -> (parent) Position2D : %fx%f\n", position2D.x, position2D.y)
    #endif
    return position2D;
}

float2 initialize_ui_components(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, int2 local_pixel_position, int2 pixel_size, float2 anchor, unsigned char layer, int2 canvas_size) {
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvasSizef.x / canvasSizef.y;
    float2 position2D = get_ui_real_position2D(world, e, parent, local_pixel_position, anchor, canvas_size);
    int2 global_pixel_position = (int2) { ceil(((position2D.x / aspect_ratio) + 0.5f) * canvasSizef.x), ((position2D.y + 0.5f) * canvasSizef.y) };
    zox_set(e, Anchor, { anchor })
    zox_set(e, PixelPosition, { local_pixel_position })
    zox_set(e, PixelSize, { pixel_size })
    zox_set(e, TextureSize, { pixel_size })
    zox_set(e, CanvasLink, { main_canvas })
    zox_set(e, ParentLink, { parent })
    zox_set(e, Layer2D, { layer })
    zox_set(e, Position2D, { position2D })
    zox_set(e, CanvasPixelPosition, { global_pixel_position })
    return position2D;
}

float2 initialize_ui_components_2(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, int2 local_pixel_position, int2 pixel_size, float2 anchor, unsigned char layer, float2 parent_position, int2 parent_pixel_size, int2 canvas_size) {
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    float2 position2D = get_ui_real_position2D_parent(local_pixel_position, anchor, parent_position, parent_pixel_size, canvas_size_f, aspect_ratio);
    int2 global_pixel_position = (int2) { ceil(((position2D.x / aspect_ratio) + 0.5f) * canvas_size_f.x), ((position2D.y + 0.5f) * canvas_size_f.y) };
    zox_set(e, Anchor, { anchor })
    zox_set(e, PixelSize, { pixel_size })
    zox_set(e, TextureSize, { pixel_size })
    zox_set(e, CanvasLink, { main_canvas })
    zox_set(e, ParentLink, { parent })
    zox_set(e, Layer2D, { layer })
    zox_set(e, PixelPosition, { local_pixel_position })
    zox_set(e, Position2D, { position2D })
    zox_set(e, CanvasPixelPosition, { global_pixel_position })
    return position2D;
}

void on_element_parent_updated(ecs_world_t *world, ecs_entity_t e, int2 local_pixel_position, float2 anchor, float2 parent_position, int2 parent_pixel_size, float2 canvas_size) {
    float aspect_ratio = canvas_size.x / canvas_size.y;
    float2 position2D = get_ui_real_position2D_parent(local_pixel_position, anchor, parent_position, parent_pixel_size, canvas_size, aspect_ratio);
    int2 global_pixel_position = (int2) { ceil(((position2D.x / aspect_ratio) + 0.5f) * canvas_size.x), ((position2D.y + 0.5f) * canvas_size.y) };
    zox_set(e, Position2D, { position2D })
    zox_set(e, CanvasPixelPosition, { global_pixel_position })
}

// set children position as well
void set_ui_transform(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, unsigned char layer, int2 canvas_size) {
    #ifdef debug_ui_scaling
        zox_log("    - layer [%i] Repositioning entity [%lu]\n", layer, e)
    #endif
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvasSizef.x / canvasSizef.y;
    if (!ecs_is_valid(world, e)) return;
    if (zox_has(e, PixelPosition)) {
        const PixelPosition *pixelPosition = zox_get(e, PixelPosition)
        const Anchor *anchor = zox_get(e, Anchor)
        int2 position = pixelPosition->value;
        float2 position2D = get_ui_real_position2D(world, e, parent, position, anchor->value, canvas_size);
        int2 global_pixel_position = (int2) { ceil((position2D.x / aspect_ratio + 0.5f) * canvasSizef.x), ((position2D.y + 0.5f) * canvasSizef.y) };
        zox_set(e, Position2D, { position2D })
        zox_set(e, CanvasPixelPosition, { global_pixel_position })
        #ifdef debug_ui_scaling
            zox_log("        -> to [%ix%i]\n", global_pixel_position.x, global_pixel_position.y)
        #endif
    }
    if (!headless && zox_has(e, MeshVertices2D)) {  //! Resize (if visible)
        const PixelSize *pixelSize = zox_get(e, PixelSize)
        const MeshAlignment *meshAlignment = zox_get(e, MeshAlignment)
        MeshVertices2D *meshVertices2D = zox_get_mut(e, MeshVertices2D)
        float2 scale2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, scale2D);
        zox_modified(e, MeshVertices2D)
        zox_set(e, MeshDirty, { 1 })
        #ifdef debug_ui_scaling
            zox_log("        -> Scaling: [%fx%f]\n", scale2D.x, scale2D.y)
        #endif
    }
    if (zox_has(e, Children)) {
        layer++;
        const Children *children = zox_get(e, Children)
        for (int i = 0; i < children->length; i++) set_ui_transform(world, children->value[i], e, layer, canvas_size);
    }
}
