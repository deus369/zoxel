ecs_entity_t particle2DPrefab;
//! Spawns a Particle2D Prefab.
void SpawnPrefabParticle2D(ecs_world_t *world)
{
    particle2DPrefab = ecs_new_prefab(world, "Particle2D");
    ecs_add(world, particle2DPrefab, Particle2D);
    // ecs_override(world, particle2DPrefab, Particle2D);
    ecs_set(world, particle2DPrefab, Position2D, { { 0, 0 } });
    ecs_override(world, particle2DPrefab, Position2D);
    ecs_set(world, particle2DPrefab, Rotation2D, { 0 });
    ecs_override(world, particle2DPrefab, Rotation2D);
    ecs_set(world, particle2DPrefab, Scale1D, { 1 });
    ecs_override(world, particle2DPrefab, Scale1D);
    // rendering
    ecs_add(world, particle2DPrefab, Brightness);
    ecs_override(world, particle2DPrefab, Brightness);
    // timing
    ecs_add(world, particle2DPrefab, DestroyInTime);
    ecs_override(world, particle2DPrefab, DestroyInTime);
    #ifdef Zoxel_Physics2D
    ecs_set(world, particle2DPrefab, Velocity2D, { { 0, 0 } });
    ecs_override(world, particle2DPrefab, Velocity2D);
    ecs_set(world, particle2DPrefab, Acceleration2D, { { 0, 0 } });
    ecs_override(world, particle2DPrefab, Acceleration2D);
    ecs_set(world, particle2DPrefab, Torque2D, { 0 });
    ecs_override(world, particle2DPrefab, Torque2D);
    #endif
}