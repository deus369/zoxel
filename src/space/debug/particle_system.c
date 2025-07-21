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
        const ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world, 0, test_particle_zone_spawn_rate, float3_scale(big_old_particle_zone_bounds, 2), test_color);
        big_old_particle_zone = particle3D_emitter;
    }
}

void toggle_character_particles(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_r) {
        const color test_color = (color) { 0, 255, 255, 200 };
        const float test_scale = 4; // 2
        const float test_rate = 32; // 4
        // conjure the canvas
        const ecs_entity_t realm = local_realm;
        zox_geter(realm, GameLink, gameLink)
        zox_geter(gameLink->value, PlayerLinks, players)
        const ecs_entity_t player = players->value[0];
        zox_geter(player, CharacterLink, characterLink)
        // our logic stuff
        // spawn particle system
        zox_get_muter(characterLink->value, Children, children)
        const ecs_entity_t previous_particles = children->length > 0 && zox_has(children->value[children->length - 1], Particle3DEmitter) ? children->value[children->length - 1] : 0;
        if (previous_particles) {
            zox_log(" + removing particles from character")
            zox_delete(previous_particles)
        } else {
            zox_log(" + adding particles to character")
            // zox_geter_value(characterLink->value, Bounds3D, float3, bounds)
            const ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world,
                characterLink->value,
                test_rate,
                float3_single(test_scale), // float3_scale(bounds, test_scale),
                test_color);
            add_to_Children(children, particle3D_emitter);
        }
        // not linked to skill
        // zox_set(particle3D_emitter, SkillLink, { character })
    }
}