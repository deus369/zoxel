// notes: to test, set terrain to 1x1x1 chunks, disable physics, enable this systems logging
ecs_entity_t spawn_chunk_character(ecs_world_t *world, ecs_entity_t_array_d* entities, const vox_file *vox, float3 position, float4 rotation, unsigned char character_lod) {
    ecs_entity_t e = spawn_character3D(world, prefab_character3D, vox, position, rotation, character_lod);
    add_to_ecs_entity_t_array_d(entities, e);
    return e;
}

ecs_entity_t spawn_chunk_character2(ecs_world_t *world, const vox_file *vox, float3 position, float4 rotation, unsigned char character_lod) {
    ecs_entity_t e = spawn_character3D(world, prefab_character3D, vox, position, rotation, character_lod);
    return e;
}

void Characters3DSpawnSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 2);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 3);
    const RenderLod *renderLods = ecs_field(it, RenderLod, 4);
    EntityLinks *entityLinks = ecs_field(it, EntityLinks, 5); // set characters
    GenerateChunkEntities *generateChunkEntities = ecs_field(it, GenerateChunkEntities, 6);
    for (int i = 0; i < it->count; i++) {
        GenerateChunkEntities *generateChunkEntities2 = &generateChunkEntities[i];
        if (generateChunkEntities2->value != zox_chunk_entities_state_triggered) continue;
        const ChunkOctree *chunkOctree = &chunkOctrees[i];
        if (chunkOctree->nodes == NULL) continue;   // if basically all air or solid, no need to spawn
        const RenderLod *renderLod = &renderLods[i];
        EntityLinks *entityLinks2 = &entityLinks[i];
        if (entityLinks2->length != 0) {
            // if already spawned, skip spawning, only update LODs
            generateChunkEntities2->value = zox_chunk_entities_state_spawned;
            continue;
        }
        #ifndef zox_disable_characters3D
            unsigned char camera_distance = renderLod->value;
            unsigned char character_lod = get_character_division_from_camera(camera_distance);
            // zoxel_log("characters spawning in chunk %lu\n", it->entities[i]);
            // find if chunk has any air position - free place to spawn - spawn characters in this chunk
            const ChunkPosition *chunkPosition = &chunkPositions[i];
            int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, default_chunk_size);
            ecs_entity_t_array_d* entities = create_ecs_entity_t_array_d();
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
                int vox_file_index = rand() % vox_files_count;
                vox_file vox = vox_files[vox_file_index];
                int3 global_voxel_position = int3_add(chunk_voxel_position, byte3_to_int3(local_position));
                float3 position = (float3) { global_voxel_position.x, global_voxel_position.y, global_voxel_position.z };
                float3_multiply_float_p(&position, terrain_voxel_scale);
                float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
                // todo: use character bounds before spawning, scale voxel position by terrain scale
                position.y += 0.26f; // 0.75f;
                position.y += 0.06f; // extra
                spawn_chunk_character(world, entities, &vox, position, rotation, character_lod);
            }
            clear_memory_component(EntityLinks, entityLinks2);
            entityLinks2->length = entities->size;
            entityLinks2->value = finalize_ecs_entity_t_array_d(entities);
            on_memory_component_created(entityLinks2, EntityLinks)
        #endif
        generateChunkEntities2->value = zox_chunk_entities_state_spawned;
        // zoxel_log(" > chunk characters were triggered %i\n", entityLinks2->length);
    }
    #ifdef zoxel_log_characters_count
        if (characters_count != 0) zoxel_log(" + characters [%i]\n", characters_count);
    #endif
} zox_declare_system(Characters3DSpawnSystem)
