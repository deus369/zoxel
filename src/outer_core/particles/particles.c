#ifndef zoxel_particles
#define zoxel_particles

#include "particles2D/particles2D.c"
#include "particles3D/particles3D.c"

//! zoxel_particles Module
void ParticlesImport(ecs_world_t *world)
{
    zoxel_module(Particles)
    zoxel_import_module(Particles2D)
    zoxel_import_module(Particles3D)
}
#endif