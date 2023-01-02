#ifndef zoxel_particles2D
#define zoxel_particles2D

// Tags
ECS_DECLARE(Particle2D);
// prefabs
#include "prefabs/particle2D.c"
// systems
#include "systems/particle2D_spawn_system.c"

//! Particle 2Ds Module.
void Particles2DImport(ecs_world_t *world)
{
    zoxel_module(Particles2D)
    ECS_TAG_DEFINE(world, Particle2D);
    SpawnPrefabParticle2D(world);
}
#endif