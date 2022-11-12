// a quick & dirty lookup for uis
ecs_entity_t canvas;
ecs_entity_t ui_entities[128];
int ui_entities_count = 0;

void add_ui_components(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, Element);
    zoxel_add_tag(world, e, ElementRender);
    zoxel_add_component(world, e, PixelPosition);
    zoxel_add_component(world, e, PixelSize);
    zoxel_add_component(world, e, Anchor);
    zoxel_add_component(world, e, CanvasLink);
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

void initialize_ui_components(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 position, int2 size, float2 anchor)
{
    const PixelSize *canvasSize = ecs_get(world, canvas, PixelSize);
    float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 position2D;
    if (parent != canvas)
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
        ui_entities[ui_entities_count] = e;
        ui_entities_count++;
        position2D = (float2) { 
            ((position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspectRatio,
            ((position.y  / canvasSizef.y) - 0.5f + anchor.y) };
        // printf("- Position2D : %fx%f\n", position2D.x, position2D.y);
    }
    ecs_set(world, e, Position2D, { position2D });
    float2 scaledSize2D = (float2) { size.x / canvasSizef.y, size.y / canvasSizef.y };
    ecs_set(world, e, Anchor, { anchor });
    ecs_set(world, e, PixelPosition, { position });
    ecs_set(world, e, PixelSize, { size });
    ecs_set(world, e, TextureSize, { size });
    ecs_set(world, e, CanvasLink, { canvas });
    ecs_set(world, e, ParentLink, { parent });
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, textured2DShader);
    spawn_gpu_texture(world, e);
    set_mesh_indicies_world(world, e, square_indicies, 6);
    set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
}

// set children position as well

void set_ui_transform(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent, float2 canvasSizef)
{
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    // resize
    const PixelSize *pixelSize = ecs_get(world, e, PixelSize);
    float2 scaledSize2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
    set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
    ecs_set(world, e, EntityDirty, { 1 });
    // reposition
    const PixelPosition *pixelPosition = ecs_get(world, e, PixelPosition);
    const Anchor *anchor = ecs_get(world, e, Anchor);
    int2 position = pixelPosition->value;
    float2 position2D;
    if (parent != canvas)
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
    }
    ecs_set(world, e, Position2D, { position2D });

    if (ecs_has(world, e, Children))
    {
        const Children *children = ecs_get(world, e, Children);
        for (int i = 0; i < children->length; i++)
        {
            ecs_entity_t child = children->value[i];
            set_ui_transform(world, child, e, canvasSizef);
        }
    }
}

//! Reposition uis after viewport resizes.
void uis_on_viewport_resized(ecs_world_t *world, int width, int height)
{
    //printf("uis_on_viewport_resized\n");
    float2 canvasSizef = { (float) width, (float) height };
    // float aspectRatio = canvasSizef.x / canvasSizef.y;
    #ifdef debug_viewport_resize
    printf("Canvas [%lu] - [%ix%i]\n", (long int) canvas, canvasSizef.x, canvasSizef.y);
    #endif
    for (int i = 0; i < ui_entities_count; i++)
    {
        ecs_entity_t e = ui_entities[i];
        #ifdef debug_viewport_resize
        printf("    e [%i] - [%lu]\n", i, (long int) e);
        #endif
        set_ui_transform(world, e, canvas, canvasSizef);
    }
}

    /*
    float2 position2D = {
        ((pixelPosition->value.x  / canvasSizef.x) - 0.5f + anchor->value.x) * aspectRatio,
        ((pixelPosition->value.y  / canvasSizef.y) - 0.5f + anchor->value.y) };
    ecs_set(world, e, Position2D, { position2D });*/
