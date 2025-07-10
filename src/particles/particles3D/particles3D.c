#ifndef zox_mod_particles3D
#define zox_mod_particles3D

#include "data/settings.c"
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
    add_hook_load_shader(&spawn_shaders_particles3D);
    zox_define_tag(Particle3D)
    zox_define_tag(Particle3DEmitter)
    zox_system_1(Particle3DEmitSystem, EcsPreStore,
        [in] transforms3.d.Position3D,
        [in] particles.ParticleEmitRate,
        [in] generic.Bounds3D,
        [in] colorz.Color,
        [none] Particle3DEmitter)
    // if making rotation ones, just create new systems, add [none] transforms3.d.Rotation3D - for this one
    zox_render3D_plus_system(Particle3DRenderSystem,
        [in] transforms3.d.Position3D,
        [in] colorz.Color,
        [none] Particle3D)
    spawn_prefabs_particles3D(world);
zox_end_module(Particles3D)

#endif
