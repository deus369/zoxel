#ifndef Zoxel_Particles
#define Zoxel_Particles
//! Zoxel_Particles Module

// Prefabs
// #include "Prefabs/Particle.c"
// Tags
ECS_DECLARE(Particle);
// Systems
// #include "Systems/ParticlesSpawnSystem.c"

void ParticlesImport(ecs_world_t *world)
{
    ECS_MODULE(world, Particles);
    ECS_TAG_DEFINE(world, Particle);
    // SpawnPrefabParticle(world);
}
#endif