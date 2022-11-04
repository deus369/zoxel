#ifndef Zoxel_Particles3D
#define Zoxel_Particles3D

// Tags
ECS_DECLARE(Particle);
// prefabs
#include "prefabs/Particle.c"
// systems
#include "systems/ParticleSpawnSystem.c"

//! Zoxel_Particles 3D Module
void Particles3DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Particles3D);
    ECS_TAG_DEFINE(world, Particle);
    SpawnPrefabParticle(world);
}
#endif