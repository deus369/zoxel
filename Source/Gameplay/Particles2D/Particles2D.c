#ifndef Zoxel_Particles2D
#define Zoxel_Particles2D
//! Zoxel_Particles2D Module
/**
 * \todo ? idk
*/

ecs_entity_t particle2DPrefab;
// Tags
ECS_DECLARE(Particle2D);
// Systems
#include "Systems/Particles2DSpawnSystem.c"

void SpawnPrefabParticle2D(ecs_world_t *world)
{
    particle2DPrefab = ecs_new_prefab(world, "Particle2D");
    ecs_set(world, particle2DPrefab, Position2D, { 0, 0 });
    ecs_set(world, particle2DPrefab, Velocity2D, { 0, 0 });
    ecs_set(world, particle2DPrefab, Scale2D, { 1 });
    ecs_override(world, particle2DPrefab, Position2D);
    ecs_override(world, particle2DPrefab, Rotation2D);
    ecs_override(world, particle2DPrefab, Scale2D);
    ecs_add(world, particle2DPrefab, Brightness);
    ecs_override(world, particle2DPrefab, Brightness);
    ecs_add(world, particle2DPrefab, DestroyInTime);
    ecs_override(world, particle2DPrefab, DestroyInTime);
    #ifdef Zoxel_Physics2D
    ecs_set(world, particle2DPrefab, Acceleration2D, { 0, 0 });
    ecs_set(world, particle2DPrefab, Rotation2D, { 0 });
    ecs_set(world, particle2DPrefab, Torque2D, { 0 });
    ecs_override(world, particle2DPrefab, Velocity2D);
    ecs_override(world, particle2DPrefab, Acceleration2D);
    ecs_override(world, particle2DPrefab, Torque2D);
    #endif
}

void Particles2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Particles2D);
    ECS_TAG_DEFINE(world, Particle2D);
    SpawnPrefabParticle2D(world);
}
#endif