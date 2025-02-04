#ifndef zox_particles
#define zox_particles

zox_component(ParticleEmitRate, int)
#include "particles2D/particles2D.c"
#include "particles3D/particles3D.c"

zox_begin_module(Particles)
    zox_define_component(ParticleEmitRate)
    zox_import_module(Particles2D)
    zox_import_module(Particles3D)
zoxel_end_module(Particles)

#endif
