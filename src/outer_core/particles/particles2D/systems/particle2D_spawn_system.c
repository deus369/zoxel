//! Here for now, spawns a one man bobarmy.
void Particle2DSpawnSystem(ecs_world_t *world, float2 bobPosition, int spawnCount)
{
    float2 positionBounds = { 0.01f, 0.1f };
    const float2 velocityBounds = { 0.03f, 0.2f };
    const float torqueBounds = 12.0f;
    const float2 scaleBounds = { 0.02f, 0.13f };
    const float2 brightnessBounds = { 0.1f, 0.4f };
    const double2 lifeTime = { 0.1f, 2.0f };
    // Create a SpaceShip prefab with a Defense component.
    Position2D *position2Ds = malloc(sizeof(Position2D) * spawnCount);
    Velocity2D *velocity2Ds = malloc(sizeof(Velocity2D) * spawnCount);
    // Rotation2D *rotation2Ds = malloc(sizeof(Rotation2D) * spawnCount);
    // Acceleration2D *acceleration2Ds = malloc(sizeof(Acceleration2D) * spawnCount);
    Torque2D *torque2Ds = malloc(sizeof(Torque2D) * spawnCount);
    Scale1D *scale1Ds = malloc(sizeof(Scale1D) * spawnCount);
    Brightness *brightnesses = malloc(sizeof(Brightness) * spawnCount);
    DestroyInTime *destroyInTimes = malloc(sizeof(DestroyInTime) * spawnCount);
    for (int i = 0; i < spawnCount; i++)
    {
        position2Ds[i].value = (float2) {
            ((rand() % 101) / 100.0f) * positionBounds.y - (positionBounds.y / 2.0f),
            ((rand() % 101) / 100.0f) * positionBounds.y - (positionBounds.y / 2.0f)
        };
        position2Ds[i].value.x += bobPosition.x;
        position2Ds[i].value.y += bobPosition.y;
        velocity2Ds[i].value = (float2) { ((rand() % 101) / 100.0f) * 1.0f - 0.5f, ((rand() % 101) / 100.0f) * 1.0f - 0.5f };
        velocity2Ds[i].value = normalize2D(velocity2Ds[i].value);
        velocity2Ds[i].value = float2_multiply_float(velocity2Ds[i].value, (velocityBounds.y - velocityBounds.x));
        if (velocity2Ds[i].value.x < 0)
        {
            velocity2Ds[i].value.x -= velocityBounds.x;
        }
        else
        {
            velocity2Ds[i].value.x += velocityBounds.x;
        }
        if (velocity2Ds[i].value.y < 0)
        {
            velocity2Ds[i].value.y -= velocityBounds.x;
        }
        else
        {
            velocity2Ds[i].value.y += velocityBounds.x;
        }
        torque2Ds[i].value = ((rand() % 101) / 100.0f) * torqueBounds - (torqueBounds / 2.0f);
        scale1Ds[i].value = scaleBounds.x + ((rand() % 101) / 100.0f) * (scaleBounds.y - scaleBounds.x);
        brightnesses[i].value = brightnessBounds.x + ((rand() % 101) / 100.0f) * (brightnessBounds.y - brightnessBounds.x);
        destroyInTimes[i].value = lifeTime.x + ((rand() % 101) / 100.0f) *  (lifeTime.y - lifeTime.x);
    }
    // const ecs_entity_t *particles2DArray = 
    ecs_bulk_init(world, &(ecs_bulk_desc_t)
    {
        .count = spawnCount,
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
    free(position2Ds);
    free(velocity2Ds);
    free(torque2Ds);
    free(scale1Ds);
    free(brightnesses);
    free(destroyInTimes);
}
ECS_SYSTEM_DECLARE(Particle2DSpawnSystem);

int GetParticles2DCount(ecs_world_t *world)
{
    return ecs_count_id_with_up(world, ecs_id(Particle2D)); // count;
    // return ecs_count(world, Particle2D);
    // return ecs_count(world, Position2D);
}

void DebugParticlesSpawned(ecs_world_t *world)
{
    printf("    Particles Spawned [%i]\n", GetParticles2DCount(world));
}

    /*cs_filter_t *filter = ecs_filter(world, {
        .terms = {{ id }} // by default matches owned & inherited components
    });
    ecs_iter_t it = ecs_filter_iter(world, filter);*/
    // ecs_filter_fini(filter);
    // int32_t count = 0;
    // ecs_iter_t it = ecs_term_iter(world, &(ecs_term_t) { 
    //     .id = id,
    //     .src.flags = EcsSelf
    // });

    // it.flags |= EcsIterIsFilter;
    // it.flags |= EcsIterEvalTables;

    // while (ecs_term_next(&it)) {
    //     count += it.count;
    // }

    // return count;
        /*if (velocity2Ds[i].value.x < - velocityBounds.x)
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
        }*/
        /*if (position2Ds[i].value.x < - positionBounds.x)
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
        }*/