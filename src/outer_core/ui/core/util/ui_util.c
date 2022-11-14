// a quick & dirty lookup for uis
ecs_entity_t canvas;
ecs_entity_t ui_entities[256];
int ui_entities_count = 0;

void add_ui_components(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, Element);
    zoxel_add_tag(world, e, ElementRender);
    zoxel_add_component(world, e, PixelPosition);
    zoxel_add_component(world, e, PixelSize);
    zoxel_add_component(world, e, Anchor);
    zoxel_set_component(world, e, CanvasLink, { });
    zoxel_add_component(world, e, CanvasPixelPosition);
    zoxel_set_component(world, e, ElementLayer, { 0 });
}

void add_ui_plus_components(ecs_world_t *world, ecs_entity_t e)
{
    // generic
    add_seed(world, e, 666);
    add_dirty(world, e);
    add_texture(world, e, (int2) { });
    #ifdef zoxel_transforms2D
    add_transform2Ds(world, e);
    #endif
    add_unique_mesh_components(world, e);
    add_ui_components(world, e);
}

float2 get_ui_real_position2D(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, int2 local_pixel_position, float2 anchor)
{
    const PixelSize *canvasSize = ecs_get(world, canvas, PixelSize);
    float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 position2D;
    if (parent == canvas)
    {
        position2D = (float2) { 
            ((local_pixel_position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspectRatio,
            ((local_pixel_position.y  / canvasSizef.y) - 0.5f + anchor.y) };
        #ifdef debug_ui_positioning
        printf("-> (canvas) Position2D : %fx%f\n", position2D.x, position2D.y);
        #endif
    }
    else
    {
        const Position2D *parent_position2D = ecs_get(world, parent, Position2D);
        const PixelSize *parent_pixel_size = ecs_get(world, parent, PixelSize);
        position2D = parent_position2D->value;
        position2D = float2_add(position2D, (float2) {
            (local_pixel_position.x  / canvasSizef.x) * aspectRatio,
            (local_pixel_position.y  / canvasSizef.y)});
        float2 parent_pixel_ratio = (float2) {
            parent_pixel_size->value.x / canvasSizef.y,
            parent_pixel_size->value.y / canvasSizef.y };
        position2D = float2_add(position2D, (float2) {
            - parent_pixel_ratio.x / 2.0f,
            - parent_pixel_ratio.y / 2.0f });
        position2D = float2_add(position2D, (float2) {
            parent_pixel_ratio.x * anchor.x,
            parent_pixel_ratio.y * anchor.y });
        #ifdef debug_ui_positioning
        printf("-> (parent) Position2D : %fx%f\n", position2D.x, position2D.y);
        #endif
    }
    return position2D;
}

void initialize_ui_components(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 local_pixel_position, int2 pixel_size, float2 anchor, unsigned char layer)
{
    if (parent == canvas)
    {
        ui_entities[ui_entities_count] = e;
        ui_entities_count++;
    }
    ecs_set(world, e, Anchor, { anchor });
    ecs_set(world, e, PixelPosition, { local_pixel_position });
    ecs_set(world, e, PixelSize, { pixel_size });
    ecs_set(world, e, TextureSize, { pixel_size });
    ecs_set(world, e, CanvasLink, { canvas });
    ecs_set(world, e, ParentLink, { parent });
    ecs_set(world, e, ElementLayer, { layer });
    // set scale
    const PixelSize *canvasSize = ecs_get(world, canvas, PixelSize);
    float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 position2D = get_ui_real_position2D(world, e, parent, local_pixel_position, anchor);
    ecs_set(world, e, Position2D, { position2D });
    int2 global_pixel_position = (int2) {
        ceil((position2D.x / aspectRatio + 0.5f) * canvasSizef.x),
        ((position2D.y + 0.5f) * canvasSizef.y) };
    ecs_set(world, e, CanvasPixelPosition, { global_pixel_position });
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, textured2DShader);
    spawn_gpu_texture(world, e);
    set_mesh_indicies_world(world, e, square_indicies, 6);
    float2 scaledSize2D = (float2) { pixel_size.x / canvasSizef.y, pixel_size.y / canvasSizef.y };
    set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
    #ifdef debug_ui_scaling
    printf("    -> Scaling: [%fx%f]\n", scaledSize2D.x, scaledSize2D.y);
    #endif
    // printf("Layer: %i\n", layer);
    // printf("> global_pixel_position [%ix%i] :: [%ix%i] -- [%fx%f]\n",
    //     global_pixel_position.x, global_pixel_position.y,
    //     size.x, size.y,
    //     position2D.x, position2D.y);
    // printf("> initialize_ui_components [%lu]\n", (long int) e);
}

// set children position as well
void set_ui_transform(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, float2 canvasSizef, unsigned char layer)
{
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    // reposition
    if (ecs_has(world, e, PixelPosition))
    {
        const PixelPosition *pixelPosition = ecs_get(world, e, PixelPosition);
        const Anchor *anchor = ecs_get(world, e, Anchor);
        int2 position = pixelPosition->value;
        float2 position2D = get_ui_real_position2D(world, e, parent, position, anchor->value);
        ecs_set(world, e, Position2D, { position2D });
        int2 global_pixel_position = (int2) {
            ceil((position2D.x / aspectRatio + 0.5f) * canvasSizef.x),
            ((position2D.y + 0.5f) * canvasSizef.y) };
        ecs_set(world, e, CanvasPixelPosition, { global_pixel_position });
        // ecs_set(world, e, ElementLayer, { layer });
        // printf("Layer: %i\n", layer);
    }
    else
    {
        printf("UI doesn't have pixel position: %lu\n", (long int) e);
    }
    //! Resize (if visible)
    if (ecs_has(world, e, MeshVertices))
    {
        const PixelSize *pixelSize = ecs_get(world, e, PixelSize);
        float2 scaledSize2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
        ecs_set(world, e, EntityDirty, { 1 });
        #ifdef debug_ui_scaling
        printf("    -> Scaling: [%fx%f]\n", scaledSize2D.x, scaledSize2D.y);
        #endif
    }
    if (ecs_has(world, e, Children))
    {
        layer++;
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++)
        {
            ecs_entity_t child = children->value[i];
            set_ui_transform(world, child, e, canvasSizef, layer);
        }
    }
}

//! Reposition uis after viewport resizes.
void uis_on_viewport_resized(ecs_world_t *world, int width, int height)
{
    ecs_set(world, canvas, PixelSize, { { width, height } });
    float2 canvasSizef = { (float) width, (float) height };
    #ifdef debug_viewport_resize
    printf("Canvas [%lu] - [%fx%f]\n", (long int) canvas, canvasSizef.x, canvasSizef.y);
    printf("    --> [%ix%i]\n", width, height);
    #endif
    for (int i = 0; i < ui_entities_count; i++)
    {
        ecs_entity_t e = ui_entities[i];
        #ifdef debug_viewport_resize
        printf("    e [%i] - [%lu]\n", i, (long int) e);
        #endif
        set_ui_transform(world, e, canvas, canvasSizef, 0);
    }
}

    /*if (parent != canvas)
    {
        const Position2D *parent_position2D = ecs_get(world, parent, Position2D);
        position2D = parent_position2D->value;
        position2D = float2_add(position2D,
            (float2) {(position.x  / canvasSizef.x) * aspectRatio, (position.y  / canvasSizef.y)});
        const PixelSize *parent_pixel_size = ecs_get(world, parent, PixelSize);
        float2 parent_pixel_ratio = (float2) {
            parent_pixel_size->value.x / canvasSizef.y,
            parent_pixel_size->value.y / canvasSizef.y };
        position2D = float2_add(position2D, (float2) {
                - parent_pixel_ratio.x / 2.0f,
                - parent_pixel_ratio.y / 2.0f });
        position2D = float2_add(position2D, (float2) {
                parent_pixel_ratio.x * anchor.x,
                parent_pixel_ratio.y * anchor.y });
        // printf("> Position2D : %fx%f\n", position2D.x, position2D.y);
    }
    else
    {
        position2D = (float2) { 
            ((position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspectRatio,
            ((position.y  / canvasSizef.y) - 0.5f + anchor.y) };
        // printf("- Position2D : %fx%f\n", position2D.x, position2D.y);
    }*/


/*
float2 position2D = {
    ((pixelPosition->value.x  / canvasSizef.x) - 0.5f + anchor->value.x) * aspectRatio,
    ((pixelPosition->value.y  / canvasSizef.y) - 0.5f + anchor->value.y) };
ecs_set(world, e, Position2D, { position2D });*/


        /*if (parent != canvas)
        {
            const Position2D *parent_position2D = ecs_get(world, parent, Position2D);
            position2D = parent_position2D->value;
            position2D = float2_add(position2D,
                (float2) {(position.x  / canvasSizef.x) * aspectRatio, (position.y  / canvasSizef.y)});
            const PixelSize *parent_pixel_size = ecs_get(world, parent, PixelSize);
            float2 parent_pixel_ratio = (float2) {
                parent_pixel_size->value.x / canvasSizef.y,
                parent_pixel_size->value.y / canvasSizef.y };
            position2D = float2_add(position2D, (float2) {
                    - parent_pixel_ratio.x / 2.0f,
                    - parent_pixel_ratio.y / 2.0f });
            position2D = float2_add(position2D, (float2) {
                    parent_pixel_ratio.x * anchor->value.x,
                    parent_pixel_ratio.y * anchor->value.y });
            #ifdef debug_viewport_resize
            printf("     - position [%fx%f]\n", position2D.x, position2D.y);
            #endif
        }
        else
        {
            position2D = (float2) { 
                ((position.x  / canvasSizef.x) - 0.5f + anchor->value.x) * aspectRatio,
                ((position.y  / canvasSizef.y) - 0.5f + anchor->value.y) };
            #ifdef debug_viewport_resize
            printf("        - position [%fx%f]\n", position2D.x, position2D.y);
            #endif
            // printf("> global_pixel_position [%ix%i]\n", global_pixel_position.x, global_pixel_position.y);
        }*/