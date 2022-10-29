//! Called in ecs updates
void CameraFollow2DSystem(ecs_iter_t *it)
{
    ecs_query_t *playerCharacter2DQuery = it->ctx;
    if (!playerCharacter2DQuery)
    {
        printf("[404; CameraFollow2DSystem - playerCharacter2DQuery is void]\n");
        return;
    }
    ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacter2DQuery);
    ecs_query_next(&playerCharacterIterator);
    if (playerCharacterIterator.count == 0)
    {
        return;
    }
    // printf("PlayerCharacter2Ds [%i]\n", playerCharacterIterator.count);
    const Position2D *playerCharacterPosition2Ds = ecs_field(&playerCharacterIterator, Position2D, 2);
    Position *positions = ecs_field(it, Position, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Position2D *playerPosition2D = &playerCharacterPosition2Ds[0];
        Position *position = &positions[i];
        position->value.x = playerPosition2D->value.x;
        position->value.y = playerPosition2D->value.y;
    }
}
ECS_SYSTEM_DECLARE(CameraFollow2DSystem);