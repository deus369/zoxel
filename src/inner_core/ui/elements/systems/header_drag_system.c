void drag_ui(ecs_world_t *world, ecs_entity_t e, int2 drag_value)
{
    if (!ecs_is_valid(world, e))
    {
        return;
    }
    /*int2 pixel_position = ecs_get(world, e, PixelPosition)->value;
    pixel_position.x += drag_value.x;
    pixel_position.y += drag_value.y;
    ecs_set(world, e, PixelPosition, { pixel_position });*/
    PixelPosition *pixel_position = ecs_get_mut(world, e, PixelPosition);
    pixel_position->value.x += drag_value.x;
    pixel_position->value.y += drag_value.y;
    ecs_modified(world, e, PixelPosition);
    #ifdef debug_element_position_change_query
        printf("Dragging window [%lu]\n", (long int) e);
    #endif
}

// if pixel position moves, update real position
// if it updates, also update any childrens positions too
// has to also move children and their children
//! Plays a Sound when button is clicked
void HeaderDragSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    const DragableState *dragableStates = ecs_field(it, DragableState, 2);
    const DraggingDelta *draggingDeltas = ecs_field(it, DraggingDelta, 3);
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 4);
    for (int i = 0; i < it->count; i++)
    {
        const DragableState *dragableState = &dragableStates[i];
        if (dragableState->value == 1)
        {
            const DraggingDelta *draggingDelta = &draggingDeltas[i];
            if (draggingDelta->value.x != 0 || draggingDelta->value.y != 0)
            {
                const ParentLink *parentLink = &parentLinks[i];
                drag_ui(world, parentLink->value, draggingDelta->value);
            }
        }
    }
}
zoxel_declare_system(HeaderDragSystem)