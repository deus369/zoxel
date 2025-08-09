#ifndef zox_particles2D
#define zox_particles2D

zox_tag(Particle2D);
#include "prefabs/particle2D.c"
#include "systems/particle2D_spawn_system.c"

void spawn_prefabs_particles2D(ecs_world_t *world) {
    spawn_prefab_particle2D(world);
}

zox_begin_module(Particles2D)
    zox_define_tag(Particle2D);
zox_end_module(Particles2D)

#endif
