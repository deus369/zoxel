#ifndef zoxel_particles3D
#define zoxel_particles3D

// Tags
ECS_DECLARE(Particle3D);
// prefabs
#include "prefabs/particle3D.c"
// systems
#include "systems/particle3D_spawn_system.c"

//! zoxel_particles 3D Module
void Particles3DImport(ecs_world_t *world)
{
    zoxel_module(Particles3D)
    ECS_TAG_DEFINE(world, Particle3D);
    SpawnPrefabParticle(world);
}
#endif