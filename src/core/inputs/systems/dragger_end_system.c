// DraggerLink - get mouse
//! Simply pushes mouse data into Raycaster component
void DraggerEndSystem(ecs_iter_t *it)
{
    // printf("MouseRaycasterSystem [%i]\n", it->count);
    DragableState *dragableStates = ecs_field(it, DragableState, 1);
    DraggerLink *draggerLinks = ecs_field(it, DraggerLink, 2);
    DraggingDelta *draggingDeltas = ecs_field(it, DraggingDelta, 3);
    for (int i = 0; i < it->count; i++)
    {
        DraggerLink *draggerLink = &draggerLinks[i];
        if (draggerLink->value == 0)
        {
            continue;
        }
        DraggingDelta *draggingDelta = &draggingDeltas[i];
        const Mouse *mouse = ecs_get(it->world, draggerLink->value, Mouse);
        if (mouse->left.wasReleasedThisFrame)
        {
            DragableState *dragableState = &dragableStates[i];
            dragableState->value = 0;
            draggerLink->value = 0;
            draggingDelta->value = (int2) { 0, 0 };
            printf("Ended dragging.\n");
        }
        else
        {
            draggingDelta->value = mouse->delta;
        }
    }
}
ECS_SYSTEM_DECLARE(DraggerEndSystem);