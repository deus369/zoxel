// a quick & dirty lookup for uis
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

//! Reposition uis after viewport resizes.
void uis_on_viewport_resized(int width, int height)
{
    //printf("uis_on_viewport_resized\n");
    float2 canvasSizef2 = { (float) width, (float) height };
    float aspectRatio = canvasSizef2.x / canvasSizef2.y;
    for (int i = 0; i < ui_entities_count; i++)
    {
        ecs_entity_t e = ui_entities[i];
        //printf("    e [%i] - [%lu]\n", i, (long int) e);
        const PixelPosition *pixelPosition = ecs_get(world, e, PixelPosition);
        const Anchor *anchor = ecs_get(world, e, Anchor);
        float2 position2D = {
            ((pixelPosition->value.x  / canvasSizef2.x) - 0.5f + anchor->value.x) * aspectRatio,
            ((pixelPosition->value.y  / canvasSizef2.y) - 0.5f + anchor->value.y) };
        const PixelSize *pixelSize = ecs_get(world, e, PixelSize);
        float2 scaledSize2D = (float2) { pixelSize->value.x / canvasSizef2.y, pixelSize->value.y / canvasSizef2.y };
        set_mesh_vertices_world_scale2D(world, e, squareTexturedVerts2, 16, scaledSize2D);  // scale the mesh
        ecs_set(world, e, Position2D, { position2D });
        ecs_set(world, e, EntityDirty, { 1 });
    }
}