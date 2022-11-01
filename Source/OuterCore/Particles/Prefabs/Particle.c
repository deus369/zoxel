ecs_entity_t particlePrefab;
//! Spawns a Particle Prefab.
void SpawnPrefabParticle(ecs_world_t *world)
{
    ecs_entity_t prefab = ecs_new_prefab(world, "Particle");
    ecs_add(world, prefab, Particle);
    // ecs_override(world, prefab, Particle2D);
    ecs_set(world, prefab, Position, { { 0, 0, 0 } });
    ecs_override(world, prefab, Position);
    ecs_set(world, prefab, Rotation, { { 0, 0, 0, 1 } });
    ecs_override(world, prefab, Rotation);
    ecs_set(world, prefab, Scale1D, { 1 });
    ecs_override(world, prefab, Scale1D);
    // rendering
    ecs_add(world, prefab, Brightness);
    ecs_override(world, prefab, Brightness);
    // timing
    ecs_add(world, prefab, DestroyInTime);
    ecs_override(world, prefab, DestroyInTime);
    #ifdef Zoxel_Physics
    ecs_set(world, prefab, Velocity, { 0 });
    ecs_override(world, prefab, Velocity);
    ecs_set(world, prefab, Acceleration, { { 0, 0 } });
    ecs_override(world, prefab, Acceleration);
    // ecs_set(world, prefab, Torque, { 0 });
    // ecs_override(world, prefab, Torque);
    #endif
    particlePrefab = prefab;
}