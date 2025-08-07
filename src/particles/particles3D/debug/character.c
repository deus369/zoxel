extern ecs_entity_t get_linked_character(ecs_world_t*, ecs_entity_t);

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
        ecs_entity_t character = get_linked_character(world, player);
        if (!character) return;
        // our logic stuffee
        // spawn particle system
        zox_get_muter(character, Children, children);
        const ecs_entity_t previous_particles = children->length > 0 && zox_has(children->value[children->length - 1], Particle3DEmitter) ? children->value[children->length - 1] : 0;
        if (previous_particles) {
            zox_log(" + removing particles from character")
            zox_delete(previous_particles)
        } else {
            zox_log(" + adding particles to character")
            // zox_geter_value(characterLink->value, Bounds3D, float3, bounds)
            const ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world,
                character,
                test_rate,
                float3_single(test_scale), // float3_scale(bounds, test_scale),
                test_color);
            add_to_Children(children, particle3D_emitter);
        }
        // not linked to skill
        // zox_set(particle3D_emitter, SkillLink, { character })
    }
}