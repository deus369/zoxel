// notes: to test, set terrain to 1x1x1 chunks, disable physics, enable this systems logging
int characters_count = 0;

void Characters3DSpawnSystem(ecs_iter_t *it) {
    float vox_scale = model_scale; //  * overall_voxel_scale;
    // vox_scale = (1.0f / 16.0f) / 2.0f;
    int3 chunk_size = (int3) { default_chunk_length, default_chunk_length, default_chunk_length };
    unsigned char did_do = 0;
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 2);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 3);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 4);
    for (int i = 0; i < it->count; i++) {
        const GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value) {
            const ChunkOctree *chunkOctree = &chunkOctrees[i];
            // if basically all air or solid, no need to spawn
            if (chunkOctree->nodes == NULL) {
                // zoxel_log(" > chunk is closed at [%ix%ix%i] \n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
                continue;
            }
            /*zoxel_log(" > length [%i] - chunk spawning [%ix%ix%i] \n", default_chunk_length,
                chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
            zoxel_log(" > chunk_voxel_position [%ix%ix%i] \n",
                chunk_voxel_position.x, chunk_voxel_position.y, chunk_voxel_position.z);*/
            // find if chunk has any air position - free place to spawn
            // spawn characters in this chunk
            for (unsigned char j = 0; j < characters_per_chunk_count; j++) {
                byte3 local_position = (byte3) { rand() % default_chunk_length, rand() % default_chunk_length, rand() % default_chunk_length };    // rand() % 16
                byte3 local_position2 = local_position;
                unsigned char voxel = get_octree_voxel(chunkOctree, &local_position2, max_octree_depth);
                if (voxel != 0) {
                    continue;
                }
                int vox_file_index = rand() % vox_files_count;
                vox_file vox = vox_files[vox_file_index];
                const ChunkPosition *chunkPosition = &chunkPositions[i];
                int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, chunk_size);
                float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
                int3 global_voxel_position = int3_add(chunk_voxel_position, int3_from_byte3(local_position));
                float3 position = (float3) { global_voxel_position.x, global_voxel_position.y, global_voxel_position.z };
                // until we get meshes centering sorted 
                /*position.x += 0.5f;
                position.y += 0.5f;
                position.z += 0.5f;*/
                /*zoxel_log("     + character at [%fx%fx%f] - [%ix%ix%i] \n",
                    position.x, position.y, position.z,
                    local_position.x, local_position.y, local_position.z);*/
                spawn_character3D(it->world, character3D_prefab, &vox, position, rotation, vox_scale);
                // add_to_ecs_entity_t_array_d(characters, e);
                // zoxel_log(" + chunk spawning character [%fx%fx%f] \n", position.x, position.y, position.z);
                characters_count++;
            }
            did_do = 1;
        }
    }
    if (did_do) {
        #ifdef zoxel_log_characters_count
            zoxel_log(" + characters [%i]\n", characters_count);
        #endif
    }
}
zoxel_declare_system(Characters3DSpawnSystem)