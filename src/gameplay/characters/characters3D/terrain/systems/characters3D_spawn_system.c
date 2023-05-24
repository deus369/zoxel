// notes: to test, set terrain to 1x1x1 chunks, disable physics, enable this systems logging
int characters_count = 0;

void Characters3DSpawnSystem(ecs_iter_t *it) {
    unsigned char did_do = 0;
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 2);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 3);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 4);
    const RenderLod *renderLods = ecs_field(it, RenderLod, 5);
    EntityLinks *entityLinks = ecs_field(it, EntityLinks, 6); // set characters
    for (int i = 0; i < it->count; i++) {
        const GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value == 0) continue;
        const ChunkOctree *chunkOctree = &chunkOctrees[i];
        if (chunkOctree->nodes == NULL) continue;   // if basically all air or solid, no need to spawn
        const RenderLod *renderLod = &renderLods[i];
        EntityLinks *entityLinks2 = &entityLinks[i];
        unsigned char camera_distance = renderLod->value;
        unsigned char character_lod = get_character_division_from_camera(camera_distance);
        did_do = 1;
        // zoxel_log("characters spawning in chunk %lu\n", it->entities[i]);
        // find if chunk has any air position - free place to spawn - spawn characters in this chunk
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, default_chunk_size);
        // initialize_memory_component(entityLinks2, ecs_entity_t, characters_per_chunk_count);
        // int k = 0;
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
            float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
            int3 global_voxel_position = int3_add(chunk_voxel_position, int3_from_byte3(local_position));
            float3 position = (float3) { global_voxel_position.x, global_voxel_position.y, global_voxel_position.z };
            float3_multiply_float_p(&position, terrain_voxel_scale);
            // todo: use character bounds before spawning, scale voxel position by terrain scale
            position.y += 0.75f;
            ecs_entity_t e = spawn_character3D(it->world, prefab_character3D, &vox, position, rotation, character_lod);
            // entityLinks2->value[j] = e;
            // add to a dynamic list here, as not always do we add characters
            // entities.add(e);
            add_to_ecs_entity_t_array_d(entities, e);
            // k++;
            // zoxel_log(" + chunk spawning character [%fx%fx%f] \n", position.x, position.y, position.z);
            characters_count++;
        }
        if (entityLinks2->length != 0) {
            free(entityLinks2->value);
        }
        entityLinks2->length = entities->size;
        entityLinks2->value = finalize_ecs_entity_t_array_d(entities);
    }
    if (did_do) {
        #ifdef zoxel_log_characters_count
            zoxel_log(" + characters [%i]\n", characters_count);
        #endif
    }
}
zox_declare_system(Characters3DSpawnSystem)