void drag_ui(ecs_world_t *world, ecs_entity_t e, int2 drag_value)
{
    if (!ecs_is_valid(world, e))
    {
        return;
    }
    int2 pixel_position = ecs_get(world, e, PixelPosition)->value;
    pixel_position.x += drag_value.x;
    pixel_position.y += drag_value.y;
    ecs_set(world, e, PixelPosition, { pixel_position });
}

// if pixel position moves, update real position
// if it updates, also update any childrens positions too
// has to also move children and their children
//! Plays a Sound when button is clicked
void HeaderDragSystem(ecs_iter_t *it)
{
    const DragableState *dragableStates = ecs_field(it, DragableState, 2);
    const DraggingDelta *draggingDeltas = ecs_field(it, DraggingDelta, 3);
    for (int i = 0; i < it->count; i++)
    {
        const DragableState *dragableState = &dragableStates[i];
        if (dragableState->value == 1)
        {
            const DraggingDelta *draggingDelta = &draggingDeltas[i];
            if (draggingDelta->value.x != 0 || draggingDelta->value.y != 0)
            {
                ecs_entity_t e = it->entities[i];
                ecs_world_t *world = it->world;
                ecs_entity_t parent = ecs_get(world, e, ParentLink)->value;
                drag_ui(world, parent, draggingDelta->value);
            }
        }
    }
}
ECS_SYSTEM_DECLARE(HeaderDragSystem);

// PixelPosition *pixelPositions = ecs_field(it, PixelPosition, 4);
// Position2D *position2Ds = ecs_field(it, Position2D, 5);
/*PixelPosition *pixelPosition = &pixelPositions[i];
pixelPosition->value.x += draggingDelta->value.x;
pixelPosition->value.y -= draggingDelta->value.y;
ecs_entity_t canvas = ecs_get(world, e, CanvasLink)->value;
int2 canvas_size = ecs_get(world, canvas, PixelSize)->value;
float2 anchor = ecs_get(world, e, Anchor)->value;
Position2D *position2D = &position2Ds[i];
position2D->value = get_ui_real_position2D(world, e,
    parent, pixelPosition->value, anchor, canvas_size);*/

// printf("- Header at [%ix%i].\n", pixelPosition->value.x, pixelPosition->value.y);
// printf("    -> Dragging header [%ix%i].\n", draggingDelta->value.x, draggingDelta->value.y);

/*ecs_entity_t canvas = ecs_get(world, e, CanvasLink)->value;
if (!ecs_is_valid(world, canvas))
{
    return;
}*/
// int2 canvas_size = ecs_get(world, canvas, PixelSize)->value;
// float2 anchor = ecs_get(world, e, Anchor)->value;
// ecs_entity_t parent = canvas; // 0; //ecs_get(world, e, ParentLink)->value;
//float2 real_position2D = get_ui_real_position2D(world, e,
//    parent, pixel_position, anchor, canvas_size);
//ecs_set(world, e, Position2D, { real_position2D });