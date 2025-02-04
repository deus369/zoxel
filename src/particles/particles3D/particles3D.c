#ifndef zox_mod_particles3D
#define zox_mod_particles3D

// stats
// #define zox_disable_particles_gpu_instancing
int zox_statistics_particles3D = 0;
#define zox_max_particles3D 100000
zox_declare_tag(Particle3D)
zox_declare_tag(Particle3DEmitter)
#include "shaders/particle_shader.c"
#include "prefabs/prefabs.c"
#include "util/debug.c"
#include "util/spawn.c"
#include "systems/particle3D_emit_system.c"
#include "systems/particle3D_spawn_system.c"
#include "systems/particle3D_render_system.c"

void update_statistics_particles3D() {
    zox_statistics_particles3D = 0;
}

zox_begin_module(Particles3D)
add_load_shader_function(&spawn_shaders_particles3D);
zox_define_tag(Particle3D)
zox_define_tag(Particle3DEmitter)
zox_system_1(Particle3DEmitSystem, zox_pip_mainthread, [in] Position3D, [in] ParticleEmitRate, [in] Bounds3D, [in] Color, [none] Particle3DEmitter)
// if making rotation ones, just create new systems, add [none] Rotation3D - for this one
zox_render3D_plus_system(Particle3DRenderSystem, [in] Position3D, [in] Color, [none] Particle3D)
spawn_prefabs_particles3D(world);
zoxel_end_module(Particles3D)

#endif
