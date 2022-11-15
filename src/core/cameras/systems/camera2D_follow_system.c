//! Called in ecs updates
void CameraFollow2DSystem(ecs_iter_t *it)
{
    // printf("PlayerCharacter2Ds [%i]\n", playerCharacterIterator.count);
    const FreeRoam *freeRoams = ecs_field(it, FreeRoam, 2);
    const CameraTarget *cameraTargets = ecs_field(it, CameraTarget, 3);
    Position *positions = ecs_field(it, Position, 4);
    Rotation *rotations = ecs_field(it, Rotation, 5);
    // player positions
    for (int i = 0; i < it->count; i++)
    {
        const FreeRoam *freeRoam = &freeRoams[i];
        if (freeRoam->value == 0)
        {
            const CameraTarget *cameraTarget = &cameraTargets[i];
            float3 target_position = { 0, 0, 0 };
            if (ecs_has(it->world, cameraTarget->value, Position2D))
            {
                const Position2D *playerPosition2D = ecs_get(it->world, cameraTarget->value, Position2D);
                target_position.x = playerPosition2D->value.x;
                target_position.y = playerPosition2D->value.y;
            }
            else if (ecs_has(it->world, cameraTarget->value, Position))
            {
                const Position *playerPosition = ecs_get(it->world, cameraTarget->value, Position);
                target_position.x = playerPosition->value.x;
                target_position.y = playerPosition->value.y;
            }
            else
            {
                continue;
            }
            Position *position = &positions[i];
            position->value.x = target_position.x;
            position->value.y = target_position.y;
            Rotation *rosition = &rotations[i];
            rosition->value = float4_identity();
        }
    }
}
ECS_SYSTEM_DECLARE(CameraFollow2DSystem);


    /*ecs_query_t *playerCharacter2DQuery = it->ctx;
    if (!playerCharacter2DQuery)
    {
        printf("[CameraFollow2DSystem; playerCharacter2DQuery is null]\n");
        return;
    }
    ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacter2DQuery);
    ecs_query_next(&playerCharacterIterator);
    if (playerCharacterIterator.count == 0)
    {
        return;
    }*/
    // const Position2D *playerCharacterPosition2Ds = ecs_field(&playerCharacterIterator, Position2D, 2);