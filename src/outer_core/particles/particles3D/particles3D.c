#ifndef zoxel_particles3D
#define zoxel_particles3D

zox_declare_tag(Particle3D)
#include "prefabs/particle3D.c"
#include "systems/particle3D_spawn_system.c"

void spawn_prefabs_particles3D(ecs_world_t *world) {
    spawn_prefab_particle3D(world);
}

zox_begin_module(Particles3D)
zox_define_tag(Particle3D)
zoxel_end_module(Particles3D)

#endif