// notes: to test, set terrain to 1x1x1 chunks, disable physics, enable this systems logging
// get function from AI module for now
// todo: reorganize, perhaps move t this module up to gameplay - or a world module, that handles terrain better procedural generation stuff
extern ecs_entity_t spawn_character3D_npc(ecs_world_t *world, ecs_entity_t_array_d* entities, const vox_file *vox, const float3 position, const float4 rotation, const unsigned char character_lod, const unsigned char render_disabled);

void Characters3DSpawnSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ChunkLodDirty, chunkLodDirtys, 1)
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(ChunkPosition, chunkPositions, 3)
    zox_field_in(RenderLod, renderLods, 4)
    zox_field_in(RenderDisabled, renderDisableds, 5)
    zox_field_out(EntityLinks, entityLinkss, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        if (chunkLodDirty->value != 3) continue;
        zox_field_i_in(ChunkOctree, chunkOctrees, chunkOctree)
        if (chunkOctree->nodes == NULL) continue;   // if basically all air or solid, no need to spawn
        zox_field_i_in(RenderLod, renderLods, renderLod)
        zox_field_i_in(RenderDisabled, renderDisableds, renderDisabled)
        zox_field_i_out(EntityLinks, entityLinkss, entityLinks)
        // if already spawned, skip spawning, only update LODs
        if (entityLinks->length) continue;
#ifdef zox_disable_npcs
        continue;
#endif
        const unsigned char vox_lod = get_voxes_lod_from_camera_distance(renderLod->value);
        // zoxel_log("characters spawning in chunk %lu\n", it->entities[i]);
        // find if chunk has any air position - free place to spawn - spawn characters in this chunk
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, default_chunk_size);
        ecs_entity_t_array_d* entities = create_ecs_entity_t_array_d(initial_dynamic_array_size);
        for (unsigned char j = 0; j < characters_per_chunk_count; j++) {
            byte3 local_position = (byte3) { rand() % default_chunk_length, default_chunk_length - 1, rand() % default_chunk_length };    // rand() % 16
            byte3 local_position_temp = local_position;
            unsigned char voxel = get_octree_voxel(chunkOctree, &local_position_temp, max_octree_depth);
            if (voxel != 0) continue;
            unsigned char did_find_ground = 0;
            for (local_position.y = default_chunk_length - 2; local_position.y >= 0; local_position.y--) {
                local_position_temp = local_position;
                voxel = get_octree_voxel(chunkOctree, &local_position_temp, max_octree_depth);
                if (voxel != 0) {
                    local_position.y++;
                    did_find_ground = 1;
                    // zoxel_log(" > found ground! [%i]\n", local_position.y);
                    break;
                }
                if (local_position.y == 0) break;   // since byte cannot go under 0
            }
            if (!did_find_ground) continue;
            int vox_index = rand() % npc_vox_index_count;
            vox_file vox = vox_files[npc_vox_indexes[vox_index]];
            int3 global_voxel_position = int3_add(chunk_voxel_position, byte3_to_int3(local_position));
            float3 position = (float3) { global_voxel_position.x, global_voxel_position.y, global_voxel_position.z };
            float3_multiply_float_p(&position, terrain_voxel_scale);
            float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
            position.y += 0.26f; // 0.75f;
            position.y += 0.06f; // extra
            spawn_character3D_npc(world, entities, &vox, position, rotation, vox_lod, renderDisabled->value);
        }
        clear_memory_component(EntityLinks, entityLinks);
        entityLinks->length = entities->size;
        entityLinks->value = finalize_ecs_entity_t_array_d(entities);
        on_memory_component_created(entityLinks, EntityLinks)
    }
} zox_declare_system(Characters3DSpawnSystem)
