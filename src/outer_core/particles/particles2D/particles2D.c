#ifndef Zoxel_Particles2D
#define Zoxel_Particles2D
//! Zoxel_Particles2D Module

// Tags
ECS_DECLARE(Particle2D);
// prefabs
#include "prefabs/Particle2D.c"
// systems
#include "systems/Particle2DSpawnSystem.c"

void Particles2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Particles2D);
    ECS_TAG_DEFINE(world, Particle2D);
    SpawnPrefabParticle2D(world);
}
#endif