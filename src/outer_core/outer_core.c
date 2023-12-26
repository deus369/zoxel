#ifndef zoxel_outer_core
#define zoxel_outer_core

#include "cubes/cubes.c"
#include "ai/ai.c"
#include "particles/particles.c"

void initialize_outer_core(ecs_world_t *world) {
    initialize_particles(world);
}

void spawn_prefabs_outer_core(ecs_world_t *world) {
    spawn_prefabs_cubes(world);
    spawn_prefabs_particles(world);
}

zox_begin_module(OuterCore)
zox_import_module(Cubes)
zox_import_module(AI)
zox_import_module(Particles)
zoxel_end_module(OuterCore)

#endif
