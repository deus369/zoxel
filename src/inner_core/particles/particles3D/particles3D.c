#ifndef zoxel_particles3D
#define zoxel_particles3D

// components
zox_declare_tag(Particle3D)
zox_declare_tag(Particle3DEmitter)
// shaders
#include "shaders/particle_shader.c"
// prefabs
#include "prefabs/particle3D.c"
#include "prefabs/particle3D_emitter.c"
// systems
#include "systems/particle3D_emit_system.c"
#include "systems/particle3D_spawn_system.c"
#include "systems/particle3D_render_system.c"

int get_count_particle3Ds(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Particle3D));
}

int get_count_particle3D_emitters(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Particle3DEmitter));
}

void initialize_particles3D(ecs_world_t *world) {
    if (!is_using_vulkan) initialize_shader_particle3D();
}

void spawn_prefabs_particles3D(ecs_world_t *world) {
    spawn_prefab_particle3D(world);
    spawn_prefab_particle3D_emitter(world);
    // spawn_particle3D_emitter(world, 0); // testing
}

zox_begin_module(Particles3D)
// components
zox_define_tag(Particle3D)
zox_define_tag(Particle3DEmitter)
// systems
zox_system_1(Particle3DEmitSystem, main_thread_pipeline, [none] Particle3DEmitter, [in] Position3D, [in] ParticleEmitRate)
if (!headless) zox_render3D_system(Particle3DRenderSystem, [none] Particle3D, [in] Position3D, [in] Rotation3D, [in] Scale1D, [in] ColorRGB)
zoxel_end_module(Particles3D)

#endif
