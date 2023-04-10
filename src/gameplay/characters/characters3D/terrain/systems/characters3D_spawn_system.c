int characters_count = 0;

void Characters3DSpawnSystem(ecs_iter_t *it) {
    unsigned char did_do = 0;
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 2);
    const ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 3);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 4);
    for (int i = 0; i < it->count; i++) {
        const GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value) {
            const ChunkOctree *chunkOctree = &chunkOctrees[i];
            // if basically all air or solid, no need to spawn
            const ChunkPosition *chunkPosition = &chunkPositions[i];
            if (chunkOctree->nodes == NULL) {
                // zoxel_log(" > chunk is closed at [%ix%ix%i] \n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
                continue;
            }
            // find if chunk has any air position - free place to spawn
            // spawn characters in this chunk
            for (unsigned char j = 0; j < characters_per_chunk_count; j++) {
                byte3 local_position = (byte3) { rand() % 16, rand() % 16, rand() % 16 };
                // byte3 local_position = (byte3) { 15, 15, 15 };
                unsigned char voxel = get_octree_voxel(chunkOctree, &local_position, max_octree_depth);
                if (voxel != 0) {
                    continue;
                }
                int vox_file_index = rand() % vox_files_count;
                vox_file vox = vox_files[vox_file_index];
                // const ChunkPosition *chunkPosition = &chunkPositions[i];
                float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
                int3 global_voxel_position = (int3) {
                    chunkPosition->value.x * 16 + local_position.x,
                    chunkPosition->value.y * 16 + local_position.y,
                    chunkPosition->value.z * 16 + local_position.z };
                float3 position = (float3) { global_voxel_position.x, global_voxel_position.y, global_voxel_position.z };
                // position.x += 8; position.y += 8; position.z += 8;
                position.y += 8.0f; // because ?? idk positions arn't perfect atm
                position.x += 0.5f;
                position.y += 0.5f;
                position.z += 0.5f;
                // zoxel_log(" > chunk spawning character [%ix%ix%i] \n", local_position.x, local_position.y, local_position.z);
                spawn_character3D(it->world, character3D_prefab, &vox, position, rotation, model_scale * overall_voxel_scale, 1);
                // add_to_ecs_entity_t_array_d(characters, e);
                // zoxel_log(" + chunk spawning character [%fx%fx%f] \n", position.x, position.y, position.z);
                characters_count++;
            }
            did_do = 1;
        }
    }
    if (did_do) {
        zoxel_log(" + characters [%i]\n", characters_count);
    }
}
zoxel_declare_system(Characters3DSpawnSystem)

/*unsigned char all_children_null = 1;
for (unsigned char i = 0; i < octree_length; i++) {
    if (chunkOctree->nodes[i].nodes != NULL) {
        all_children_null = 0;
        break;
    }
}
if (all_children_null) {
    zoxel_log(" > chunk child nodes are closed at [%ix%ix%i] \n", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z);
    continue;
}*/