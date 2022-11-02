//! Called in ecs updates
void PlayerRoamSystem(ecs_iter_t *it)
{
    // QueryContainer2 *queryContainer2 = (QueryContainer2*) it->ctx;
    ecs_query_t *cameraQuery = it->ctx; // queryContainer2->query1;
    if (!cameraQuery)
    {
        printf("[CameraMoveSystem; cameraQuery is null]\n");
        return;
    }
    ecs_iter_t cameraIter = ecs_query_iter(it->world, cameraQuery);
    ecs_query_next(&cameraIter);
    if (cameraIter.count == 0)
    {
        return;
    }
    // return;
    /*ecs_query_t *playerQuery = queryContainer2->query2;
    if (!playerQuery)
    {
        printf("[CameraMoveSystem; playerQuery is null]\n");
        return;
    }
    ecs_iter_t playerIter = ecs_query_iter(it->world, playerQuery);
    ecs_query_next(&playerIter);
    if (playerIter.count == 0)
    {
        return;
    }*/
    Mouse *mouses = ecs_field(it, Mouse, 1);
    CameraFree *cameraFrees = ecs_field(&cameraIter, CameraFree, 2);
    // DisableMovement *disableMovements = ecs_field(&playerIter, DisableMovement, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Mouse *mouse = &mouses[i];
        for (int j = 0; j < cameraIter.count; j++)
        {
            CameraFree *cameraFree = &cameraFrees[j];
            if (mouse->right.wasPressedThisFrame)
            {
                cameraFree->value = !cameraFree->value;
                printf("Camera Free Toggled [%s]\n", cameraFree->value ? "true" : "false");
            }
        }
    }
}
ECS_SYSTEM_DECLARE(PlayerRoamSystem);

void PlayerRoamSystem2(ecs_iter_t *it)
{
    ecs_query_t *playerQuery = it->ctx;
    if (!playerQuery)
    {
        printf("[CameraMoveSystem; playerQuery is null]\n");
        return;
    }
    ecs_iter_t playerIter = ecs_query_iter(it->world, playerQuery);
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
            if (mouse->right.wasPressedThisFrame)
            {
                disableMovement->value = !disableMovement->value;
                printf("DisableMovement Toggled [%s]\n", disableMovement->value ? "true" : "false");
            }
        }
    }
}
ECS_SYSTEM_DECLARE(PlayerRoamSystem2);


// rotate = float3_multiply_float(rotate, rotatePower);
// rotateQuaternion = float4_multiply_float(rotateQuaternion, rotatePower);
/*float4 rotateY = quaternion_from_euler((float3) { 0, -mouse->delta.x * rotatePower, 0 });
float4 rotateZ = quaternion_from_euler((float3) { 0, 0, -mouse->delta.y * rotatePower });
float4 rotateQuaternion = { 0, 0, 0, 1 };
rotateQuaternion = quaternion_rotate(rotateQuaternion, rotateY);
rotateQuaternion = quaternion_rotate(rotateQuaternion, rotateZ);*/