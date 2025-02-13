// notes: to test, set terrain to 1x1x1 chunks, disable physics, enable this systems logging
// get function from AI module for now
// todo: reorganize, perhaps move t this module up to gameplay - or a world module, that handles terrain better procedural generation stuff
extern ecs_entity_t spawn_character3D_npc(ecs_world_t *world, ecs_entity_t_array_d* entities, const ecs_entity_t vox, const float3 position, const float4 rotation, const byte character_lod, const byte render_disabled);
// default_chunk_length
// todo: predict spawn size from octree?
// todo: handle bounds resize by shifting positions
void Characters3DSpawnSystem(ecs_iter_t *it) {
    if (disable_npcs) {
        return;
    }
    zox_field_world()
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(ChunkPosition, chunkPositions, 3)
    zox_field_in(RenderDistance, renderDistances, 4)
    zox_field_in(RenderDisabled, renderDisableds, 5)
    zox_field_out(EntityLinks, entityLinkss, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != chunk_lod_state_characters_spawn) continue;
        zox_field_i(ChunkOctree, chunkOctrees, chunkOctree)
        if (chunkOctree->nodes == NULL) continue;   // if basically all air or solid, no need to spawn
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        zox_field_o(EntityLinks, entityLinkss, entityLinks)
        // if already spawned, skip spawning, only update LODs
        if (entityLinks->length) continue;
        const byte vox_lod = get_voxes_lod_from_camera_distance(renderDistance->value);
        // find if chunk has any air position - free place to spawn - spawn characters in this chunk
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, default_chunk_size);
        ecs_entity_t_array_d* entities = create_ecs_entity_t_array_d(initial_dynamic_array_size);
        for (byte j = 0; j < characters_per_chunk_count; j++) {
            byte3 local_position = find_position_in_chunk(chunkOctree, max_octree_depth);
            if (byte3_equals(byte3_full, local_position)) continue;
            float3 position = local_to_real_position_character(local_position, chunk_voxel_position, (float3) { 0.5f, 0.5f, 0.5f });
            float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
            int vox_index = rand() % npc_vox_index_count;
            const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data(npc_voxes[vox_index]));
            if (vox) {
                spawn_character3D_npc(world, entities, vox, position, rotation, vox_lod, renderDisabled->value);
            } else {
                zox_log(" ! vox not found for [%s]\n", npc_voxes[vox_index])
            }
            // ecs_entity_t vox = files_voxes[npc_vox_indexes[vox_index]];
        }
        clear_memory_component(EntityLinks, entityLinks);
        entityLinks->length = entities->size;
        entityLinks->value = finalize_ecs_entity_t_array_d(entities);
        on_memory_component_created(entityLinks, EntityLinks)
    }
} zox_declare_system(Characters3DSpawnSystem)
