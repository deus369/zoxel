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
        /*float4 rotation = quaternion_identity;
        byte character_lod = 0;
        byte render_disabled = 0;
        int vox_index = rand() % npc_vox_index_count;
        const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data(npc_voxes[vox_index]));
        spawn_character3D_data spawn_data = {
            .prefab = prefab_character3_npc,
            .vox = vox,
            .position = position,
            .rotation = rotation,
            .lod = character_lod,
            .render_disabled = render_disabled,
        };
        const ecs_entity_t e = spawn_character3(world, spawn_data);
        zox_set(e, ChunkLink, { chunk })*/
    }
}