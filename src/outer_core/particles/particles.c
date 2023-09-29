#ifndef zoxel_particles
#define zoxel_particles

// shared components
zox_component(ParticleEmitRate, int)
// sub modules
#include "particles2D/particles2D.c"
#include "particles3D/particles3D.c"

void spawn_prefabs_particles(ecs_world_t *world) {
    spawn_prefabs_particles2D(world);
    spawn_prefabs_particles3D(world);
}

zox_begin_module(Particles)
zox_define_component(ParticleEmitRate)
zox_import_module(Particles2D)
zox_import_module(Particles3D)
zoxel_end_module(Particles)

#endif