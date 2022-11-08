#ifndef zoxel_particles3D
#define zoxel_particles3D

// Tags
ECS_DECLARE(Particle);
// prefabs
#include "prefabs/particle3D.c"
// systems
#include "systems/particle_spawn_system.c"

//! zoxel_particles 3D Module
void Particles3DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Particles3D);
    ECS_TAG_DEFINE(world, Particle);
    SpawnPrefabParticle(world);
}
#endif