#ifndef zoxel_particles
#define zoxel_particles

// Sub Modules
#include "particles2D/particles2D.c"
#include "particles3D/particles3D.c"

//! zoxel_particles Module
void ParticlesImport(ecs_world_t *world)
{
    zoxel_module(Particles)
    ECS_IMPORT(world, Particles2D);
    ECS_IMPORT(world, Particles3D);
}
#endif