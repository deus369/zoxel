byte debug_colliders = 0;

void toggle_debug_character_bounds(ecs_world_t *world) {
    if (!zox_valid(local_terrain)) {
        return;
    }
    debug_colliders = !debug_colliders;
    if (debug_colliders) {
        add_physics_debug(world, prefab_character3D);
    } else {
        remove_physics_debug(world, prefab_character3D);
    }
    zox_geter(local_terrain, ChunkLinks, chunkLinks)
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hashmap_pair* pair = chunkLinks->value->data[i];
        uint checks = 0;
        while (pair != NULL && checks < max_safety_checks_hashmap) {
            ecs_entity_t chunk = pair->value;
            zox_geter(chunk, EntityLinks, entityLinks)
            for (int j = 0; j < entityLinks->length; j++) {
                ecs_entity_t e2 = entityLinks->value[j];
                if (debug_colliders) {
                    add_physics_debug(world, e2);
                } else {
                    remove_physics_debug(world, e2);
                }
            }
            pair = pair->next;
            checks++;
        }
    }
}

void key_down_toggle_debug_character_bounds(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_z) {
        toggle_debug_character_bounds(world);
    }
}

// todo: pass player entity through here
void test_spawn_character_npc(ecs_world_t *world, int32_t keycode) {
    // zox_log("keydown %i\n", keycode)
    if (keycode == SDLK_l) {
        // spawn at here
        int3 chunk_position = int3_zero;
        float3 position = (float3) { 4, 12, 4 };

        const ecs_entity_t terrain = zox_get_value(local_realm, TerrainLink)
        if (!terrain) {
            return;
        }

        zox_geter(terrain, ChunkLinks, chunk_links)
        const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
        if (!chunk) {
            return;
        }

        // zox_log("+ spawning npc!\n")
        float4 rotation = quaternion_identity;
        byte character_lod = 0;
        byte render_disabled = 0;
        int vox_index = rand() % npc_vox_index_count;
        const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data(npc_voxes[vox_index]));
        spawn_character3D_data spawn_data = {
            .prefab = prefab_character3D_npc,
            .vox = vox,
            .position = position,
            .rotation = rotation,
            .lod = character_lod,
            .render_disabled = render_disabled,
        };
        const ecs_entity_t e = spawn_character3D(world, spawn_data);
        zox_set(e, ChunkLink, { chunk })
    }
}