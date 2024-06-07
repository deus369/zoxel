#ifndef zox_mod_particles3D
#define zox_mod_particles3D

zox_declare_tag(Particle3D)
zox_declare_tag(Particle3DEmitter)
#include "shaders/particle_shader.c"
#include "prefabs/prefabs.c"
#include "util/debug.c"
#include "util/spawn.c"
#include "systems/particle3D_emit_system.c"
#include "systems/particle3D_spawn_system.c"
#include "systems/particle3D_render_system.c"

zox_begin_module(Particles3D)
add_load_shader_function(&spawn_shaders_particles3D);
zox_define_tag(Particle3D)
zox_define_tag(Particle3DEmitter)
zox_system_1(Particle3DEmitSystem, zox_pip_mainthread, [in] Position3D, [in] ParticleEmitRate, [in] Bounds3D, [none] Particle3DEmitter)
zox_render3D_system(Particle3DRenderSystem, [none] Particle3D, [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] Color)
spawn_prefabs_particles3D(world);
zoxel_end_module(Particles3D)

#endif
