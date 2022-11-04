#ifndef Zoxel_Particles
#define Zoxel_Particles

// Sub Modules
#include "particles2D/particles2D.c"
#include "particles3D/particles3D.c"

//! Zoxel_Particles Module
void ParticlesImport(ecs_world_t *world)
{
    ECS_MODULE(world, Particles);
    ECS_IMPORT(world, Particles2D);
    ECS_IMPORT(world, Particles3D);
}
#endif