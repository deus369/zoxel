//! Using mouse - or action - activate a ui element.
void ElementActivateSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    const Mouse *mouses = ecs_field(it, Mouse, 1);
    const RaycasterTarget *raycasterTargets = ecs_field(it, RaycasterTarget, 2);
    for (int i = 0; i < it->count; i++)
    {
        const RaycasterTarget *raycasterTarget = &raycasterTargets[i];
        if (raycasterTarget->value == 0)
        {
            continue;
        }
        const Mouse *mouse = &mouses[i];
        if (mouse->left.wasPressedThisFrame)
        {
            // if (ecs_has(it->world, raycasterTarget->value, CloseButton))
            //  printf("Clicked UI: [%lu]\n", (long int) raycasterTarget->value);
            if (ecs_has(world, raycasterTarget->value, Clickable))
            {
                // ecs_set(world, raycasterTarget->value, ClickableState, { 1 });
                ClickableState *clickableState = ecs_get_mut(world, raycasterTarget->value, ClickableState);
                clickableState->value = 1;
                ecs_modified(world, raycasterTarget->value, ClickableState);
            }
            // how to do this best way?
            if (ecs_has(world, raycasterTarget->value, Dragable))
            {
                DragableState *dragableState = ecs_get_mut(world, raycasterTarget->value, DragableState);
                DraggerLink *draggerLink = ecs_get_mut(world, raycasterTarget->value, DraggerLink);
                dragableState->value = 1;
                draggerLink->value = it->entities[i];
                ecs_modified(world, raycasterTarget->value, DragableState);
                ecs_modified(world, raycasterTarget->value, DraggerLink);
                //ecs_set(it->world, raycasterTarget->value, DragableState, { 1 });
                //ecs_set(it->world, raycasterTarget->value, DraggerLink, { it->entities[i] });
            }
        }
    }
}
ECS_SYSTEM_DECLARE(ElementActivateSystem);