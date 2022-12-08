//! Sets real position when pixel position updates
void ElementPositionSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    printf("Pixel positions changed!\n");
    ecs_world_t *world = it->world;
    const PixelPosition *pixelPositions = ecs_field(it, PixelPosition, 2);
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 3);
    const Anchor *anchors = ecs_field(it, Anchor, 4);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 5);
    Position2D *position2Ds = ecs_field(it, Position2D, 6);
    CanvasPixelPosition *canvasPixelPositions = ecs_field(it, CanvasPixelPosition, 7);
    for (int i = 0; i < it->count; i++)
    {
        ecs_entity_t e = it->entities[i];
        const PixelPosition *pixelPosition = &pixelPositions[i];
        const ParentLink *parentLink = &parentLinks[i];
        const Anchor *anchor = &anchors[i];
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (!ecs_is_valid(world, canvasLink->value))
        {
            continue;
        }
        int2 canvas_size = ecs_get(world, canvasLink->value, PixelSize)->value;
        Position2D *position2D = &position2Ds[i];
        position2D->value = get_ui_real_position2D(world, e,
            parentLink->value, pixelPosition->value, anchor->value, canvas_size);
        CanvasPixelPosition *canvasPixelPosition = &canvasPixelPositions[i];
        float2 canvasSizef = { (float) canvas_size.x, (float) canvas_size.y };
        float aspectRatio = canvasSizef.x / canvasSizef.y;
        canvasPixelPosition->value = (int2) {
            ceil((position2D->value.x / aspectRatio + 0.5f) * canvasSizef.x),
            ((position2D->value.y + 0.5f) * canvasSizef.y) };
    }
}
ECS_SYSTEM_DECLARE(ElementPositionSystem);