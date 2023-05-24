unsigned char debug_colliders = 0;

void toggle_collision_debug(ecs_world_t *world) {
    debug_colliders = !debug_colliders;
    const ChunkLinks *chunkLinks = ecs_get(world, main_terrain, ChunkLinks);
    // for every chunk, use entity links, add or remove physics debug components
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hash_map_pair* pair = chunkLinks->value->data[i];
        while (pair != NULL) {
            ecs_entity_t chunk_entity = pair->value;
            const EntityLinks *entityLinks = ecs_get(world, chunk_entity, EntityLinks);
            for (int j = 0; j < entityLinks->length; j++) {
                ecs_entity_t character_entity = entityLinks->value[j];
                if (debug_colliders) {
                    add_physics_debug(world, character_entity);
                } else {
                    remove_physics_debug(world, character_entity);
                }
            }
            pair = pair->next;
        }
    }
}

void PlayerShortcutsSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++) {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->v.pressed_this_frame) {
            spawn_zoxel_window(world);
        } else if (keyboard->x.pressed_this_frame) {
            toggle_ui(world, &fps_display, &spawn_fps_display);
        } else if (keyboard->c.pressed_this_frame) {
            toggle_ui(world, &quads_label, &spawn_quad_count_label);
        } else if (keyboard->z.pressed_this_frame) {
            toggle_collision_debug(world);
        } else if (keyboard->m.pressed_this_frame) {
            zoxel_log(" > generated new music\n");
            double music_speed = 0.2 + (rand() % 100) * 0.008;
            zox_set_only(main_music, MusicSpeed, { music_speed });
            zox_set_only(main_music, GenerateMusic, { 1 });
        }
    }
}
zox_declare_system(PlayerShortcutsSystem)