ecs_entity_t ui_entities[256];  // a quick & dirty lookup for uis
int ui_entities_count = 0;

void add_ui_components(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, Element);
    zox_set(e, PixelPosition, { { } });
    zox_set(e, PixelSize, { { } });
    zox_set(e, CanvasPixelPosition, { { } });
    zox_set(e, Anchor, { { } });
    zox_set(e, CanvasLink, { });
    zox_set(e, Layer2D, { 0 });
    zox_set(e, InitializeEntityMesh, { 1 });
    if (!headless) zox_add_tag(e, ElementRender);
}

void add_ui_mesh_components(ecs_world_t *world, ecs_entity_t e) {
    zox_set(e, MeshDirty, { 0 });
    zox_set(e, Brightness, { 1 });
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    prefab_set_mesh_indicies(world, e, square_indicies, 6);
    prefab_set_mesh2D_vertices(world, e, square_vertices, 4);
    prefab_set_mesh_uvs(world, e, square_uvs, 4);
}

void add_ui_plus_components(ecs_world_t *world, ecs_entity_t e) {
    add_seed(world, e, 666);
    add_dirty(world, e);
    add_transform2Ds(world, e);
    add_texture(world, e, int2_zero, 0);
    add_ui_components(world, e);
    if (!headless) add_ui_mesh_components(world, e);
}

void add_ui_plus_components_invisible(ecs_world_t *world, ecs_entity_t e) {
    add_seed(world, e, 666);
    add_transform2Ds(world, e);
    add_ui_components(world, e);
}

float2 get_ui_real_position2D(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 local_pixel_position, float2 anchor, int2 canvas_size) {
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 position2D;
    if (parent == main_canvas) {
        position2D = (float2) { 
            ((local_pixel_position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspectRatio,
            ((local_pixel_position.y  / canvasSizef.y) - 0.5f + anchor.y) };
        #ifdef debug_ui_positioning
        zoxel_log("-> (main_canvas) Position2D : %fx%f\n", position2D.x, position2D.y);
        #endif
    } else {
        if (!ecs_has(world, parent, Position2D)) {
            zoxel_log("Parent [%lu] has no Position2D component.\n", (long int) parent);
            // return (float2) { 0, 0 };
        }
        const Position2D *parent_position2D = ecs_get(world, parent, Position2D);
        const PixelSize *parent_pixel_size = ecs_get(world, parent, PixelSize);
        if (parent_position2D != NULL) {
            position2D = parent_position2D->value;
        }
        position2D = float2_add(position2D, (float2) {
            (local_pixel_position.x  / canvasSizef.x) * aspectRatio,
            (local_pixel_position.y  / canvasSizef.y)});
        if (parent_pixel_size != NULL) {
            float2 parent_pixel_ratio = (float2) {
                parent_pixel_size->value.x / canvasSizef.y,
                parent_pixel_size->value.y / canvasSizef.y };
            position2D = float2_add(position2D, (float2) {
                - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x,
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
    position2D = float2_add(position2D, (float2) {
        (local_pixel_position.x  / canvas_size_f.x) * aspect_ratio,
        (local_pixel_position.y  / canvas_size_f.y)});
    float2 parent_pixel_ratio = (float2) {
        parent_pixel_size.x / canvas_size_f.y,
        parent_pixel_size.y / canvas_size_f.y };
    position2D = float2_add(position2D, (float2) {
        - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x,
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
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 position2D = get_ui_real_position2D(world, e, parent, local_pixel_position, anchor, canvas_size);
    int2 global_pixel_position = (int2) { ceil((position2D.x / aspectRatio + 0.5f) * canvasSizef.x),
        ((position2D.y + 0.5f) * canvasSizef.y) };
    ecs_set(world, e, Anchor, { anchor });
    ecs_set(world, e, PixelPosition, { local_pixel_position });
    ecs_set(world, e, PixelSize, { pixel_size });
    ecs_set(world, e, TextureSize, { pixel_size });
    ecs_set(world, e, CanvasLink, { main_canvas });
    ecs_set(world, e, ParentLink, { parent });
    ecs_set(world, e, Layer2D, { layer });
    ecs_set(world, e, Position2D, { position2D });
    ecs_set(world, e, CanvasPixelPosition, { global_pixel_position });
    return position2D;
}

float2 initialize_ui_components_2(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 local_pixel_position, int2 pixel_size, float2 anchor, unsigned char layer,
    float2 parent_position, int2 parent_pixel_size, int2 canvas_size) {
    if (parent == main_canvas) {
        ui_entities[ui_entities_count] = e;
        ui_entities_count++;
    }
    ecs_set(world, e, Anchor, { anchor });
    ecs_set(world, e, PixelSize, { pixel_size });
    ecs_set(world, e, TextureSize, { pixel_size });
    ecs_set(world, e, CanvasLink, { main_canvas });
    ecs_set(world, e, ParentLink, { parent });
    ecs_set(world, e, Layer2D, { layer });
    // set scale
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    float2 position2D = get_ui_real_position2D_parent(local_pixel_position, anchor,
        parent_position, parent_pixel_size, canvas_size_f, aspect_ratio);
    int2 global_pixel_position = (int2) { ceil((position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x),
        ((position2D.y + 0.5f) * canvas_size_f.y) };
    ecs_set(world, e, PixelPosition, { local_pixel_position });
    ecs_set(world, e, Position2D, { position2D });
    ecs_set(world, e, CanvasPixelPosition, { global_pixel_position });
    return position2D;
}

// set children position as well
void set_ui_transform(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, unsigned char layer, int2 canvas_size) {
    #ifdef debug_ui_scaling
        zoxel_log("    - layer [%i] Repositioning entity [%lu]\n", layer, (long int) e);
    #endif
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    unsigned char is_valid = ecs_is_valid(world, e);
    // reposition
    if (is_valid && ecs_has(world, e, PixelPosition)) {
        const PixelPosition *pixelPosition = ecs_get(world, e, PixelPosition);
        const Anchor *anchor = ecs_get(world, e, Anchor);
        int2 position = pixelPosition->value;
        float2 position2D = get_ui_real_position2D(world, e, parent, position, anchor->value, canvas_size);
        ecs_set(world, e, Position2D, { position2D });
        int2 global_pixel_position = (int2) { ceil((position2D.x / aspectRatio + 0.5f) * canvasSizef.x),
            ((position2D.y + 0.5f) * canvasSizef.y) };
        ecs_set(world, e, CanvasPixelPosition, { global_pixel_position });
        #ifdef debug_ui_scaling
            zoxel_log("        -> to [%ix%i]\n", global_pixel_position.x, global_pixel_position.y);
        #endif
    } else {
        zoxel_log(" ! set_ui_transform - ui PixelPosition not found [%lu]\n", (long int) e);
    }
    //! Resize (if visible)
    if (!headless && is_valid && ecs_has(world, e, MeshVertices2D)) {
        const PixelSize *pixelSize = ecs_get(world, e, PixelSize);
        float2 scaledSize2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_world_scale2D(world, e, square_vertices, 4, scaledSize2D);  // scale the mesh
        ecs_set(world, e, MeshDirty, { 1 });
        #ifdef debug_ui_scaling
            zoxel_log("        -> Scaling: [%fx%f]\n", scaledSize2D.x, scaledSize2D.y);
        #endif
    }
    if (is_valid && ecs_has(world, e, Children)) {
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
    // int2 canvas_size = { width, height };
    ecs_set(world, main_canvas, PixelSize, { screen_size });
    #ifdef debug_viewport_resize
        zoxel_log(" > viewport resized to dimensions: [%ix%i]\n", screen_size.x, screen_size.y);
    #endif
    for (int i = 0; i < ui_entities_count; i++) {
        ecs_entity_t e = ui_entities[i];
        #ifdef debug_viewport_resize
            zoxel_log("    e [%i] - [%lu]\n", i, (long int) e);
        #endif
        set_ui_transform(world, e, main_canvas, 0, screen_size);
    }
}

//zox_add(e, MeshVertices2D);
//zox_add(e, MeshIndicies);
//zox_add(e, MeshUVs);
/*MeshUVs meshUVs = { };
initialize_memory_component_non_pointer(meshUVs, float2, 4);
memcpy(meshUVs.value, square_uvs, 4 * 8);
zox_set(e, MeshUVs, { meshUVs.length, meshUVs.value });*/