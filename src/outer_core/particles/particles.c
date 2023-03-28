#ifndef zoxel_particles
#define zoxel_particles

#include "particles2D/particles2D.c"
#include "particles3D/particles3D.c"

zoxel_begin_module(Particles)
zoxel_import_module(Particles2D)
zoxel_import_module(Particles3D)
zoxel_end_module(Particles)

#endif