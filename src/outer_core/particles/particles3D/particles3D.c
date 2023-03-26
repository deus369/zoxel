#ifndef zoxel_particles3D
#define zoxel_particles3D

zoxel_declare_tag(Particle3D)
#include "prefabs/particle3D.c"
#include "systems/particle3D_spawn_system.c"

void Particles3DImport(ecs_world_t *world) {
    zoxel_module(Particles3D)
    zoxel_define_tag(Particle3D)
    spawn_prefab_particle3D(world);
}
#endif