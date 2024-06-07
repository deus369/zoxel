ecs_entity_t prefab_particle3D;
ecs_entity_t prefab_particle3D_emitter;
#include "particle3D.c"
#include "particle3D_emitter.c"


void spawn_shaders_particles3D(ecs_world_t *world) {
    if (!is_using_vulkan) initialize_shader_particle3D();
}

void spawn_prefabs_particles3D(ecs_world_t *world) {
    prefab_particle3D = spawn_prefab_particle3D(world);
    prefab_particle3D_emitter = spawn_prefab_particle3D_emitter(world);
    // spawn_particle3D_emitter(world, 0); // testing
}
