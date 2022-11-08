//! Here for now, spawns a one man bobarmy.
void ParticleSpawnSystem(ecs_world_t *world, float2 bobPosition, int spawnCount)
{
    float2 positionBounds = { 0.1f, 0.5f };
    const float2 velocityBounds = { 0.03f, 0.2f };
    const float2 scaleBounds = { 0.02f, 0.13f };
    const double2 lifeTime = { 0.1f, 2.0f };
    const float2 brightnessBounds = { 0.2f, 0.8f };
    // Create a SpaceShip prefab with a Defense component.
    Position *positions = malloc(sizeof(Position) * spawnCount);
    Velocity *velocitys = malloc(sizeof(Velocity) * spawnCount);
    // Rotation *rotations = malloc(sizeof(Rotation) * spawnCount);
    // Acceleration *accelerations = malloc(sizeof(Acceleration) * spawnCount);
    // Torque *torques = malloc(sizeof(Torque) * spawnCount);
    Scale1D *scale1Ds = malloc(sizeof(Scale1D) * spawnCount);
    Brightness *brightnesses = malloc(sizeof(Brightness) * spawnCount);
    DestroyInTime *destroyInTimes = malloc(sizeof(DestroyInTime) * spawnCount);
    for (int i = 0; i < spawnCount; i++)
    {
        positions[i].value = (float3) {
            ((rand() % 101) / 100.0f) * positionBounds.y - (positionBounds.y / 2.0f),
            ((rand() % 101) / 100.0f) * positionBounds.y - (positionBounds.y / 2.0f),
            ((rand() % 101) / 100.0f) * positionBounds.y - (positionBounds.y / 2.0f)
        };
        positions[i].value.x += bobPosition.x;
        positions[i].value.y += bobPosition.y;
        // velocity
        velocitys[i].value = (float3) {
            ((rand() % 101) / 100.0f) * 1.0f - 0.5f,
            ((rand() % 101) / 100.0f) * 1.0f - 0.5f,
            ((rand() % 101) / 100.0f) * 1.0f - 0.5f
        };
        velocitys[i].value = float3_normalize(velocitys[i].value);
        velocitys[i].value = float3_multiply_float(velocitys[i].value, (velocityBounds.y - velocityBounds.x));
        if (velocitys[i].value.x < 0)
        {
            velocitys[i].value.x -= velocityBounds.x;
        }
        else
        {
            velocitys[i].value.x += velocityBounds.x;
        }
        if (velocitys[i].value.y < 0)
        {
            velocitys[i].value.y -= velocityBounds.x;
        }
        else
        {
            velocitys[i].value.y += velocityBounds.x;
        }
        if (velocitys[i].value.z < 0)
        {
            velocitys[i].value.z -= velocityBounds.x;
        }
        else
        {
            velocitys[i].value.z += velocityBounds.x;
        }
        // torques[i].value = ((rand() % 101) / 100.0f) * torqueBounds - (torqueBounds / 2.0f);
        scale1Ds[i].value = scaleBounds.x + ((rand() % 101) / 100.0f) * (scaleBounds.y - scaleBounds.x);
        brightnesses[i].value = brightnessBounds.x + ((rand() % 101) / 100.0f) * (brightnessBounds.y - brightnessBounds.x);
        destroyInTimes[i].value = lifeTime.x + ((rand() % 101) / 100.0f) *  (lifeTime.y - lifeTime.x);
    }
    // const ecs_entity_t *particlesArray = 
    ecs_bulk_init(world, &(ecs_bulk_desc_t)
    {
        .count = spawnCount,
        .ids =
        {
            ecs_pair(EcsIsA, particle3D_prefab),
            ecs_id(Position),
            ecs_id(Velocity),
            ecs_id(Acceleration),
            ecs_id(Rotation),
            ecs_id(Torque),
            ecs_id(Scale1D),
            ecs_id(Brightness),
            ecs_id(DestroyInTime)
        },
        // provide data for each id
        .data = (void*[])
        {       
            NULL,           // Prefab pair, what is it used for?
            positions,
            velocitys,
            NULL,           // Acceleration
            NULL,           // Rotation
            NULL,           // Torque
            scale1Ds,
            brightnesses,
            destroyInTimes
        }
    });
    free(positions);
    free(velocitys);
    // free(torques);
    free(scale1Ds);
    free(brightnesses);
    free(destroyInTimes);
}
ECS_SYSTEM_DECLARE(ParticleSpawnSystem);