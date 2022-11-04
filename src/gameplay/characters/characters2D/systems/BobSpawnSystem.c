
bool debugSpawnBobArmy = false;

// forward declarations

int GetBobCount()
{
    return ecs_count(world, Position2D);
}

void PrintBobSpawnSystem(ecs_world_t *world)
{
    printf("    Bobs Spawned [%i]\n", GetBobCount());
}

//! Here for now, spawns a one man bobarmy.
/*void SpawnBobArmy(ecs_world_t *world, ecs_entity_t character2DPrefab, float2 bobPosition, int bobSpawnCount)
{
    float2 positionBounds = { 0.1f, 0.5f };
    const float2 velocityBounds = { 0.2f, 12.4f };
    const float torqueBounds = 12.0f;
    const float2 scaleBounds = { 0.1f, 0.23f };
    const float2 brightnessBounds = { 0.1f, 0.4f };
    const double2 lifeTime = { 0.5f, 8.0f };
    // Create a SpaceShip prefab with a Defense component.
    Position2D *position2Ds = malloc(sizeof(Position2D) * bobSpawnCount);
    Velocity2D *velocity2Ds = malloc(sizeof(Velocity2D) * bobSpawnCount);
    // Rotation2D *rotation2Ds = malloc(sizeof(Rotation2D) * bobSpawnCount);
    // Acceleration2D *acceleration2Ds = malloc(sizeof(Acceleration2D) * bobSpawnCount);
    Torque2D *torque2Ds = malloc(sizeof(Torque2D) * bobSpawnCount);
    Scale1D *scale1Ds = malloc(sizeof(Scale1D) * bobSpawnCount);
    Brightness *brightnesses = malloc(sizeof(Brightness) * bobSpawnCount);
    DestroyInTime *destroyInTimes = malloc(sizeof(DestroyInTime) * bobSpawnCount);
    for (int i = 0; i < bobSpawnCount; i++)
    {
        position2Ds[i].value = (float2) {
            ((rand() % 101) / 100.0f) * positionBounds.y - (positionBounds.y / 2.0f),
            ((rand() % 101) / 100.0f) * positionBounds.y - (positionBounds.y / 2.0f)
        };
        if (position2Ds[i].value.x < - positionBounds.x)
        {
            position2Ds[i].value.x = - positionBounds.x;
        }
        else if (position2Ds[i].value.x > positionBounds.x)
        {
            position2Ds[i].value.x = positionBounds.x;
        }
        if (position2Ds[i].value.y < - positionBounds.x)
        {
            position2Ds[i].value.y = - positionBounds.x;
        }
        else if (position2Ds[i].value.y > positionBounds.x)
        {
            position2Ds[i].value.y = positionBounds.x;
        }
        position2Ds[i].value.x += bobPosition.x;
        position2Ds[i].value.y += bobPosition.y;
        velocity2Ds[i].value = (float2) {
            ((rand() % 101) / 100.0f) * velocityBounds.y - (velocityBounds.y / 2.0f),
            ((rand() % 101) / 100.0f) * velocityBounds.y - (velocityBounds.y / 2.0f)
        };
        if (velocity2Ds[i].value.x < - velocityBounds.x)
        {
            velocity2Ds[i].value.x = - velocityBounds.x;
        }
        else if (velocity2Ds[i].value.x > velocityBounds.x)
        {
            velocity2Ds[i].value.x = velocityBounds.x;
        }
        if (velocity2Ds[i].value.y < - velocityBounds.x)
        {
            velocity2Ds[i].value.y = - velocityBounds.x;
        }
        else if (velocity2Ds[i].value.y > velocityBounds.x)
        {
            velocity2Ds[i].value.y = velocityBounds.x;
        }
        torque2Ds[i].value = ((rand() % 101) / 100.0f) * torqueBounds - (torqueBounds / 2.0f);
        scale1Ds[i].value = scaleBounds.x + ((rand() % 101) / 100.0f) * (scaleBounds.y - scaleBounds.x);
        brightnesses[i].value = brightnessBounds.x + ((rand() % 101) / 100.0f) * (brightnessBounds.y - brightnessBounds.x);
        destroyInTimes[i].value = lifeTime.x + ((rand() % 101) / 100.0f) *  (lifeTime.y - lifeTime.x);
    }
    const ecs_entity_t *bobArmy = ecs_bulk_init(world, &(ecs_bulk_desc_t)
    {
        .count = bobSpawnCount,
        .ids =
        {
            ecs_pair(EcsIsA, particle2DPrefab),
            ecs_id(Position2D),
            ecs_id(Velocity2D),
            ecs_id(Acceleration2D),
            ecs_id(Rotation2D),
            ecs_id(Torque2D),
            ecs_id(Scale1D),
            ecs_id(Brightness),
            ecs_id(DestroyInTime)
        },
        // provide data for each id
        .data = (void*[])
        {       
            NULL,           // Prefab pair, what is it used for?
            position2Ds,
            velocity2Ds,
            NULL,           // Acceleration2D
            NULL,           // Rotation2D
            torque2Ds,
            scale1Ds,
            brightnesses,
            destroyInTimes
        }
    });
}*/

//! Debug used for now, Called in main thread
/*void BobArmySpawnFixer(ecs_world_t *world)
{
    if (debugSpawnBobArmy)
    {
        debugSpawnBobArmy = false;
        SpawnBobArmy(world, character2DPrefab, bobSpawnCount);
    }
}*/