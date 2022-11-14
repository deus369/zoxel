//! Using mouse - or action - activate a ui element.
void ElementActivateSystem(ecs_iter_t *it)
{
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
            if (ecs_has(it->world, raycasterTarget->value, CloseButton))
            // printf("Clicked UI: [%lu]\n", (long int) raycasterTarget->value);
            ecs_set(it->world, raycasterTarget->value, ClickableState, { 1 });
        }
    }
}
ECS_SYSTEM_DECLARE(ElementActivateSystem);