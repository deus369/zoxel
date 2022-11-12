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

void initialize_ui_components(ecs_world_t *world, ecs_entity_t e, ecs_entity_t parent,
    int2 position, int2 size, float2 anchor)
{
    ui_entities[ui_entities_count] = e;
    ui_entities_count++;
    const PixelSize *canvasSize = ecs_get(world, canvas, PixelSize);
    float2 canvasSizef = { (float) canvasSize->value.x, (float) canvasSize->value.y };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    float2 scaledSize2D = (float2) { size.x / canvasSizef.y, size.y / canvasSizef.y };
    float2 position2D;
    if (parent != canvas)
    {
        // const PixelPosition *parent_pixel_position = ecs_get(world, parent, PixelPosition);
        // const Anchor *parent_anchor = ecs_get(world, parent, Anchor);
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
        // - scaledSize2D.y / 2.0f
        position2D = float2_add(position2D, (float2) {
                parent_pixel_ratio.x * anchor.x,
                parent_pixel_ratio.y * anchor.y });


        /*float2 parent_position2D = (float2) { 
            ((parent_pixel_position->value.x  / canvasSizef.x) - 0.5f + parent_anchor->value.x) * aspectRatio,
            ((parent_pixel_position->value.y  / canvasSizef.y) - 0.5f + parent_anchor->value.y) };*/
        /*position2D = float2_add(parent_position2D->value, (float2) { 
            ((position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspectRatio,
            ((position.y  / canvasSizef.y) - 0.5f + anchor.y) });*/
        // position = int2_add(position, parent_pixel_position->value);

        // const Position2D *parent_position2D = ecs_get(world, parent, Position2D);
        // position2D = float2_add(position2D, parent_position2D->value);
        printf("> Position2D : %fx%f\n", position2D.x, position2D.y);
    }
    else
    {
        position2D = (float2) { 
            ((position.x  / canvasSizef.x) - 0.5f + anchor.x) * aspectRatio,
            ((position.y  / canvasSizef.y) - 0.5f + anchor.y) };
        printf("- Position2D : %fx%f\n", position2D.x, position2D.y);
    }
    ecs_set(world, e, Anchor, { anchor });
    ecs_set(world, e, PixelPosition, { position });
    ecs_set(world, e, PixelSize, { size });
    ecs_set(world, e, TextureSize, { size });
    ecs_set(world, e, Position2D, { position2D });
    ecs_set(world, e, CanvasLink, { canvas });
    ecs_set(world, e, ParentLink, { parent });
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, textured2DShader);
    spawn_gpu_texture(world, e);
    set_mesh_indicies_world(world, e, square_indicies, 6);
    set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
}

//! Reposition uis after viewport resizes.
void uis_on_viewport_resized(int width, int height)
{
    //printf("uis_on_viewport_resized\n");
    float2 canvasSizef = { (float) width, (float) height };
    float aspectRatio = canvasSizef.x / canvasSizef.y;
    for (int i = 0; i < ui_entities_count; i++)
    {
        ecs_entity_t e = ui_entities[i];
        //printf("    e [%i] - [%lu]\n", i, (long int) e);
        const PixelPosition *pixelPosition = ecs_get(world, e, PixelPosition);
        const Anchor *anchor = ecs_get(world, e, Anchor);
        float2 position2D = {
            ((pixelPosition->value.x  / canvasSizef.x) - 0.5f + anchor->value.x) * aspectRatio,
            ((pixelPosition->value.y  / canvasSizef.y) - 0.5f + anchor->value.y) };
        const PixelSize *pixelSize = ecs_get(world, e, PixelSize);
        float2 scaledSize2D = (float2) { pixelSize->value.x / canvasSizef.y, pixelSize->value.y / canvasSizef.y };
        set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
        ecs_set(world, e, Position2D, { position2D });
        ecs_set(world, e, EntityDirty, { 1 });
    }
}