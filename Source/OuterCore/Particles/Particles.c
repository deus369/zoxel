#ifndef Zoxel_Particles
#define Zoxel_Particles
//! Zoxel_Particles Module

// Tags
ECS_DECLARE(Particle);
// Prefabs
#include "Prefabs/Particle.c"
// Systems
#include "Systems/ParticleSpawnSystem.c"

void ParticlesImport(ecs_world_t *world)
{
    ECS_MODULE(world, Particles);
    ECS_TAG_DEFINE(world, Particle);
    SpawnPrefabParticle(world);
}
#endif