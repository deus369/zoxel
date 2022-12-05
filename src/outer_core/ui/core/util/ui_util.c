// a quick & dirty lookup for uis
ecs_entity_t ui_entities[256];
int ui_entities_count = 0;

void add_ui_components(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, Element);
    zoxel_add_tag(world, e, ElementRender);
    zoxel_set(world, e, PixelPosition, { { } });
    zoxel_set(world, e, PixelSize, { { } });
    zoxel_set(world, e, CanvasPixelPosition, { { } });
    zoxel_set(world, e, Anchor, { { } });
    zoxel_set(world, e, CanvasLink, { });
    zoxel_set(world, e, ElementLayer, { 0 });
    zoxel_set(world, e, EntityInitialize, { 1 });
}

void add_ui_plus_components(ecs_world_t *world, ecs_entity_t e)
{
    add_seed(world, e, 666);
    add_dirty(world, e);
    add_transform2Ds(world, e);
    add_texture(world, e, (int2) { });
    add_unique_mesh_components(world, e);
    zoxel_set(world, e, MeshDirty, { 1 });
    add_ui_components(world, e);
}

void add_ui_plus_components_invisible(ecs_world_t *world, ecs_entity_t e)
{
    add_seed(world, e, 666);
    add_transform2Ds(world, e);
    add_ui_components(world, e);
}

float2 get_ui_real_position2D(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 local_pixel_position, float2 anchor, int2 canvas_size)
{
    // const PixelSize *canvasSize = ecs_get(world, main_canvas, PixelSize);
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 position2D;
    if (parent == main_canvas)
    {
        position2D = (float2) { 
            ((local_pixel_position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspectRatio,
            ((local_pixel_position.y  / canvasSizef.y) - 0.5f + anchor.y) };
        #ifdef debug_ui_positioning
        zoxel_log_arg("-> (main_canvas) Position2D : %fx%f\n", position2D.x, position2D.y);
        #endif
    }
    else
    {
        if (!ecs_has(world, parent, Position2D))
        {
            zoxel_log_arg("Parent [%lu] has no Position2D component.\n", (long int) parent);
            // return (float2) { 0, 0 };
        }
        const Position2D *parent_position2D = ecs_get(world, parent, Position2D);
        if (parent_position2D != NULL)
        {
            position2D = parent_position2D->value;
        }
        position2D = float2_add(position2D, (float2) {
            (local_pixel_position.x  / canvasSizef.x) * aspectRatio,
            (local_pixel_position.y  / canvasSizef.y)});
        const PixelSize *parent_pixel_size = ecs_get(world, parent, PixelSize);
        if (parent_pixel_size != NULL)
        {
            float2 parent_pixel_ratio = (float2) {
                parent_pixel_size->value.x / canvasSizef.y,
                parent_pixel_size->value.y / canvasSizef.y };
            position2D = float2_add(position2D, (float2) {
                - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x,
                - (parent_pixel_ratio.y / 2.0f) + parent_pixel_ratio.y * anchor.y });
        }
        #ifdef debug_ui_positioning
        zoxel_log_arg("-> (parent) Position2D : %fx%f\n", position2D.x, position2D.y);
        #endif
    }
    return position2D;
}

float2 initialize_ui_components(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 local_pixel_position, int2 pixel_size, float2 anchor, unsigned char layer, int2 canvas_size)
{
    if (parent == main_canvas)
    {
        ui_entities[ui_entities_count] = e;
        ui_entities_count++;
    }
    // set scale
    // const PixelSize *canvasSize = ecs_get(world, main_canvas, PixelSize);
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 position2D = get_ui_real_position2D(world, e, parent, local_pixel_position, anchor, canvas_size);
    int2 global_pixel_position = (int2) {
        ceil((position2D.x / aspectRatio + 0.5f) * canvasSizef.x),
        ((position2D.y + 0.5f) * canvasSizef.y) };
    ecs_set(world, e, Anchor, { anchor });
    ecs_set(world, e, PixelPosition, { local_pixel_position });
    ecs_set(world, e, PixelSize, { pixel_size });
    ecs_set(world, e, TextureSize, { pixel_size });
    ecs_set(world, e, CanvasLink, { main_canvas });
    ecs_set(world, e, ParentLink, { parent });
    ecs_set(world, e, ElementLayer, { layer });
    ecs_set(world, e, Position2D, { position2D });
    ecs_set(world, e, CanvasPixelPosition, { global_pixel_position });
    // spawn_gpu_mesh(world, e);
    // spawn_gpu_material(world, e, shader2D_textured);
    // spawn_gpu_texture(world, e);
    // set_mesh_indicies_world(world, e, square_indicies, 6);
    // float2 scaledSize2D = (float2) { pixel_size.x / canvasSizef.y, pixel_size.y / canvasSizef.y };
    // set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
    // printf("Layer: %i\n", layer);
    // printf("> global_pixel_position [%ix%i] :: [%ix%i] -- [%fx%f]\n",
    //     global_pixel_position.x, global_pixel_position.y,
    //     size.x, size.y,
    //     position2D.x, position2D.y);
    // printf("> initialize_ui_components [%lu]\n", (long int) e);
    //#ifdef debug_ui_scaling
    //printf("    -> Scaling: [%fx%f]\n", scaledSize2D.x, scaledSize2D.y);
    //#endif
    return position2D;
}

float2 get_ui_real_position2D_2(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 local_pixel_position, float2 anchor,
    float2 parent_position2D, int2 parent_pixel_size,
    int2 canvas_size)
{
    // const PixelSize *canvasSize = ecs_get(world, main_canvas, PixelSize);
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 position2D;
    position2D = parent_position2D;
    position2D = float2_add(position2D, (float2) {
        (local_pixel_position.x  / canvasSizef.x) * aspectRatio,
        (local_pixel_position.y  / canvasSizef.y)});
    float2 parent_pixel_ratio = (float2) {
        parent_pixel_size.x / canvasSizef.y,
        parent_pixel_size.y / canvasSizef.y };
    position2D = float2_add(position2D, (float2) {
        - (parent_pixel_ratio.x / 2.0f) + parent_pixel_ratio.x * anchor.x,
        - (parent_pixel_ratio.y / 2.0f) + parent_pixel_ratio.y * anchor.y });
    #ifdef debug_ui_positioning
    zoxel_log_arg("-> (parent) Position2D : %fx%f\n", position2D.x, position2D.y);
    #endif
    return position2D;
}

float2 initialize_ui_components_2(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 local_pixel_position, int2 pixel_size, float2 anchor, unsigned char layer,
    float2 parent_position2D, int2 parent_pixel_size, int2 canvas_size)
{
    if (parent == main_canvas)
    {
        ui_entities[ui_entities_count] = e;
        ui_entities_count++;
    }
    ecs_set(world, e, Anchor, { anchor });
    ecs_set(world, e, PixelPosition, { local_pixel_position });
    ecs_set(world, e, PixelSize, { pixel_size });
    ecs_set(world, e, TextureSize, { pixel_size });
    ecs_set(world, e, CanvasLink, { main_canvas });
    ecs_set(world, e, ParentLink, { parent });
    ecs_set(world, e, ElementLayer, { layer });
    // set scale
    // const PixelSize *canvasSize = ecs_get(world, main_canvas, PixelSize);
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 position2D = get_ui_real_position2D_2(world, e, parent, local_pixel_position, anchor,
        parent_position2D, parent_pixel_size, canvas_size);
    ecs_set(world, e, Position2D, { position2D });
    int2 global_pixel_position = (int2) {
        ceil((position2D.x / aspectRatio + 0.5f) * canvasSizef.x),
        ((position2D.y + 0.5f) * canvasSizef.y) };
    ecs_set(world, e, CanvasPixelPosition, { global_pixel_position });
    return position2D;
}

// set children position as well
void set_ui_transform(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, unsigned char layer, int2 canvas_size)
{
    #ifdef debug_ui_scaling
    zoxel_log_arg("    - layer [%i] Repositioning entity [%lu]\n", layer, (long int) e);
    #endif
    float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    bool is_valid = ecs_is_valid(world, e);
    // reposition
    if (is_valid && ecs_has(world, e, PixelPosition))
    {
        const PixelPosition *pixelPosition = ecs_get(world, e, PixelPosition);
        const Anchor *anchor = ecs_get(world, e, Anchor);
        int2 position = pixelPosition->value;
        float2 position2D = get_ui_real_position2D(world, e, parent, position, anchor->value, canvas_size);
        ecs_set(world, e, Position2D, { position2D });
        int2 global_pixel_position = (int2) {
            ceil((position2D.x / aspectRatio + 0.5f) * canvasSizef.x),
            ((position2D.y + 0.5f) * canvasSizef.y) };
        ecs_set(world, e, CanvasPixelPosition, { global_pixel_position });
        #ifdef debug_ui_scaling
        zoxel_log_arg("        -> to [%ix%i]\n", global_pixel_position.x, global_pixel_position.y);
        #endif
    }
    else
    {
        zoxel_log_arg("UI doesn't have pixel position: %lu\n", (long int) e);
    }
    //! Resize (if visible)
    if (is_valid && ecs_has(world, e, MeshVertices))
    {
        const PixelSize *pixelSize = ecs_get(world, e, PixelSize);
        float2 scaledSize2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
        ecs_set(world, e, MeshDirty, { 1 });
        #ifdef debug_ui_scaling
        zoxel_log_arg("        -> Scaling: [%fx%f]\n", scaledSize2D.x, scaledSize2D.y);
        #endif
    }
    if (is_valid && ecs_has(world, e, Children))
    {
        layer++;
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++)
        {
            ecs_entity_t child = children->value[i];
            set_ui_transform(world, child, e, layer, canvas_size);
        }
    }
}

//! Reposition uis after viewport resizes.
void uis_on_viewport_resized(ecs_world_t *world, int width, int height)
{
    int2 canvas_size = { width, height };
    ecs_set(world, main_canvas, PixelSize, { canvas_size });
    #ifdef debug_viewport_resize
    zoxel_log_arg("On Viewport Resized to dimensions: [%ix%i]\n", canvas_size.x, canvas_size.y);
    #endif
    for (int i = 0; i < ui_entities_count; i++)
    {
        ecs_entity_t e = ui_entities[i];
        #ifdef debug_viewport_resize
        zoxel_log_arg("    e [%i] - [%lu]\n", i, (long int) e);
        #endif
        set_ui_transform(world, e, main_canvas, 0, canvas_size);
    }
}