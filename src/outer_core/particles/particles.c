#ifndef zoxel_particles
#define zoxel_particles

#include "particles2D/particles2D.c"
#include "particles3D/particles3D.c"

zox_begin_module(Particles)
zox_import_module(Particles2D)
zox_import_module(Particles3D)
zoxel_end_module(Particles)

#endif