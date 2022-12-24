//! Called in ecs updates
void FreeCameraToggleSystem(ecs_iter_t *it)
{
    // QueryContainer2 *queryContainer2 = (QueryContainer2*) it->ctx;
    // ecs_query_t *cameraQuery = it->ctx; // queryContainer2->query1;
    ecs_iter_t cameraIter = ecs_query_iter(it->world, it->ctx);
    ecs_query_next(&cameraIter);
    if (cameraIter.count == 0)
    {
        return;
    }
    Mouse *mouses = ecs_field(it, Mouse, 1);
    FreeRoam *freeRoams = ecs_field(&cameraIter, FreeRoam, 2);
    // DisableMovement *disableMovements = ecs_field(&playerIter, DisableMovement, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Mouse *mouse = &mouses[i];
        for (int j = 0; j < cameraIter.count; j++)
        {
            FreeRoam *freeRoam = &freeRoams[j];
            if (mouse->left.pressed_this_frame)
            {
                if (freeRoam->value == 0)
                {
                    freeRoam->value = 1;
                }
                else
                {
                    freeRoam->value = 0;
                }
                // printf("Camera Free Toggled [%s]\n", freeRoam->value ? "true" : "false");
            }
        }
    }
}
ECS_SYSTEM_DECLARE(FreeCameraToggleSystem);

void FreeCameraDisableMovementSystem(ecs_iter_t *it)
{
    ecs_iter_t playerIter = ecs_query_iter(it->world, it->ctx);
    ecs_query_next(&playerIter);
    if (playerIter.count == 0)
    {
        return;
    }
    Mouse *mouses = ecs_field(it, Mouse, 1);
    DisableMovement *disableMovements = ecs_field(&playerIter, DisableMovement, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Mouse *mouse = &mouses[i];
        for (int j = 0; j < playerIter.count; j++)
        {
            DisableMovement *disableMovement = &disableMovements[j];
            if (mouse->left.pressed_this_frame)
            {
                disableMovement->value = !disableMovement->value;
                // printf("DisableMovement Toggled [%s]\n", disableMovement->value ? "true" : "false");
            }
        }
    }
}
ECS_SYSTEM_DECLARE(FreeCameraDisableMovementSystem);