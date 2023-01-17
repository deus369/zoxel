//! Here for now, spawns a one man bobarmy.
void Particle3DSpawnSystem(ecs_world_t *world, float3 bobPosition, int spawnCount)
{
    ecs_defer_begin(world);
    float2 positionBounds = { 0.1f, 0.2f };
    const float2 velocityBounds = { 0.03f, 0.2f };
    const float2 scaleBounds = { 0.02f, 0.13f };
    const double2 lifeTime = { 0.1f, 2.0f };
    const float2 brightnessBounds = { 0.2f, 0.8f };
    // Create a SpaceShip prefab with a Defense component.
    Position3D *positions = malloc(sizeof(Position3D) * spawnCount);
    Velocity3D *velocity3Ds = malloc(sizeof(Velocity3D) * spawnCount);
    // Rotation3D *rotations = malloc(sizeof(Rotation3D) * spawnCount);
    // Acceleration *accelerations = malloc(sizeof(Acceleration) * spawnCount);
    // Torque3D *torques = malloc(sizeof(Torque3D) * spawnCount);
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
        positions[i].value.z += bobPosition.z;
        // velocity
        velocity3Ds[i].value = (float3) {
            ((rand() % 101) / 100.0f) * 1.0f - 0.5f,
            ((rand() % 101) / 100.0f) * 1.0f - 0.5f,
            ((rand() % 101) / 100.0f) * 1.0f - 0.5f
        };
        velocity3Ds[i].value = float3_normalize(velocity3Ds[i].value);
        velocity3Ds[i].value = float3_multiply_float(velocity3Ds[i].value, (velocityBounds.y - velocityBounds.x));
        if (velocity3Ds[i].value.x < 0)
        {
            velocity3Ds[i].value.x -= velocityBounds.x;
        }
        else
        {
            velocity3Ds[i].value.x += velocityBounds.x;
        }
        if (velocity3Ds[i].value.y < 0)
        {
            velocity3Ds[i].value.y -= velocityBounds.x;
        }
        else
        {
            velocity3Ds[i].value.y += velocityBounds.x;
        }
        if (velocity3Ds[i].value.z < 0)
        {
            velocity3Ds[i].value.z -= velocityBounds.x;
        }
        else
        {
            velocity3Ds[i].value.z += velocityBounds.x;
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
            ecs_id(Position3D),
            ecs_id(Velocity3D),
            ecs_id(Acceleration3D),
            ecs_id(Rotation3D),
            ecs_id(Torque3D),
            ecs_id(Scale1D),
            ecs_id(Brightness),
            ecs_id(DestroyInTime)
        },
        // provide data for each id
        .data = (void*[])
        {       
            NULL,           // Prefab pair, what is it used for?
            positions,
            velocity3Ds,
            NULL,           // Acceleration3D
            NULL,           // Rotation3D
            NULL,           // Torque3D
            scale1Ds,
            brightnesses,
            destroyInTimes
        }
    });
    free(positions);
    free(velocity3Ds);
    // free(torques);
    free(scale1Ds);
    free(brightnesses);
    free(destroyInTimes);
    ecs_defer_end(world);
}
zoxel_declare_system(Particle3DSpawnSystem)