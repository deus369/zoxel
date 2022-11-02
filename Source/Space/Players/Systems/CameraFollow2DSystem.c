//! Called in ecs updates
void CameraFollow2DSystem(ecs_iter_t *it)
{
    ecs_query_t *playerCharacter2DQuery = it->ctx;
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
    }
    // printf("PlayerCharacter2Ds [%i]\n", playerCharacterIterator.count);
    const Position2D *playerCharacterPosition2Ds = ecs_field(&playerCharacterIterator, Position2D, 2);
    const CameraFree *cameraFrees = ecs_field(it, CameraFree, 2);
    // const Character2DLink *character2DLinks = ecs_field(it, Character2DLink, 3);
    Position *positions = ecs_field(it, Position, 4);
    Rotation *rotations = ecs_field(it, Rotation, 5);
    for (int i = 0; i < it->count; i++)
    {
        const CameraFree *cameraFree = &cameraFrees[i];
        if (!cameraFree->value)
        {
            // const Character2DLink *character2DLink = &character2DLinks[i];
            // const Position2D *playerPosition2D = &playerCharacterPosition2Ds[character2DLink->value];
            const Position2D *playerPosition2D = &playerCharacterPosition2Ds[0];
            Position *position = &positions[i];
            position->value.x = playerPosition2D->value.x;
            position->value.y = playerPosition2D->value.y;
            position->value.z = 1.2f;
            Rotation *rosition = &rotations[i];
            rosition->value = float4_identity();
        }
    }
}
ECS_SYSTEM_DECLARE(CameraFollow2DSystem);


            //! \todo Link camera to character, CharacterLink.
            // use character2DLink->value
            // printf("character2DLink->value: %lu\n", (long int) character2DLink->value);
            // printf("character2DLink->value: %lu\n", ecs_id(character2DLink->value));