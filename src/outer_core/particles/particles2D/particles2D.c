#ifndef zoxel_particles2D
#define zoxel_particles2D

zoxel_declare_tag(Particle2D)
#include "prefabs/particle2D.c"
#include "systems/particle2D_spawn_system.c"

zoxel_begin_module(Particles2D)
zoxel_define_tag(Particle2D)
SpawnPrefabParticle2D(world);
zoxel_end_module(Particles2D)

#endif