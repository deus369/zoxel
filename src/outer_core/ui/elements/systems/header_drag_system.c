//! Plays a Sound when button is clicked
void HeaderDragSystem(ecs_iter_t *it)
{
    const DragableState *dragableStates = ecs_field(it, DragableState, 2);
    const DraggingDelta *draggingDeltas = ecs_field(it, DraggingDelta, 3);
    PixelPosition *pixelPositions = ecs_field(it, PixelPosition, 4);
    for (int i = 0; i < it->count; i++)
    {
        const DragableState *dragableState = &dragableStates[i];
        if (dragableState->value == 1)
        {
            const DraggingDelta *draggingDelta = &draggingDeltas[i];
            if (draggingDelta->value.x != 0 || draggingDelta->value.y != 0)
            {
                PixelPosition *pixelPosition = &pixelPositions[i];
                pixelPosition->value.x += draggingDelta->value.x;
                pixelPosition->value.y += draggingDelta->value.y;
                // printf("- Header at [%ix%i].\n", pixelPosition->value.x, pixelPosition->value.y);
                // printf("    -> Dragging header [%ix%i].\n", draggingDelta->value.x, draggingDelta->value.y);
            }
        }
    }
}
ECS_SYSTEM_DECLARE(HeaderDragSystem);