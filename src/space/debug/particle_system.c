ecs_entity_t big_old_particle_zone = 0;

void toggle_test_particle_system(ecs_world_t *world, int32_t keycode) {
    const int test_particle_zone_spawn_rate = 5000;
    const float3 big_old_particle_zone_bounds = (float3) { 32, 32, 32 };
    const color test_color = (color) { 158, 118, 44, 200 };
    // max should be around 10k
    if (keycode == SDLK_l) {
        if (big_old_particle_zone) {
            zox_log("- deleting a big old particle zone")
            zox_delete(big_old_particle_zone)
            big_old_particle_zone = 0;
            return;
        }
        zox_log("+ spawning a big old particle zone")
        const ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world, 0, test_particle_zone_spawn_rate, float3_multiply_float(big_old_particle_zone_bounds, 2), test_color);
        big_old_particle_zone = particle3D_emitter;
    }
}