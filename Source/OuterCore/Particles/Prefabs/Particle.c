ecs_entity_t particlePrefab;
//! Spawns a Particle Prefab.
void SpawnPrefabParticle(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "particle_prefab");
    zoxel_add_tag(world, e, Particle);
    // ecs_override(world, prefab, Particle2D);
    zoxel_set_component(world, e, Position, { { 0, 0, 0 } });
    zoxel_set_component(world, e, Rotation, { { 0, 0, 0, 1 } });
    zoxel_set_component(world, e, Scale1D, { 1 });
    // rendering
    zoxel_add_component(world, e, Brightness);
    // timing
    zoxel_add_component(world, e, DestroyInTime);
    #ifdef Zoxel_Physics
    zoxel_set_component(world, e, Velocity, { 0 });
    zoxel_set_component(world, e, Acceleration, { { 0, 0 } });
    // ecs_set(world, prefab, Torque, { 0 });
    // ecs_override(world, prefab, Torque);
    #endif
    particlePrefab = e;
}