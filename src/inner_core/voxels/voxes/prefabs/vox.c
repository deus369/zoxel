ecs_entity_t prefab_vox;

ecs_entity_t spawn_prefab_vox(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_chunk);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_vox");
    add_chunk_colors(world, e);
    zox_set(e, Scale1D, { 1.0f })
    // because we set the data on spawn, no need to generate here
    zox_set(e, GenerateChunk, { 0 })
    zox_set(e, ChunkDirty, { 1 })
    zox_set(e, MeshDirty, { 0 })
    add_gpu_colors(world, e);
    ecs_defer_end(world);
    prefab_vox = e;
    return e;
}

void set_vox_from_vox_file(ecs_world_t *world, ecs_entity_t e, vox_file *vox) {
    #ifndef zox_disable_vox_octrees
        const unsigned char fill_type = 0;
        int3 vox_size = vox->chunks[0].size.xyz;
        unsigned char *voxels = vox->chunks[0].xyzi.voxels;
        // zoxel_log(" > setting vox [%ix%ix%i]\n", vox_size.x, vox_size.y, vox_size.z);
        ColorRGBs colorRGBs = { };
        int colors_length = vox->palette.values_length;
        initialize_memory_component_non_pointer(colorRGBs, color_rgb, colors_length);
        memcpy(colorRGBs.value, vox->palette.values_rgb, colors_length * sizeof(color_rgb));
        ecs_set(world, e, ColorRGBs, { colorRGBs.length, colorRGBs.value });
        ChunkOctree chunkOctree = { };
        unsigned char target_depth = 5;
        fill_octree(&chunkOctree, fill_type, target_depth);
        byte2 set_octree_data = (byte2) { 1, target_depth };
        int vox_index = 0;
        for (int i = 0; i < vox_size.x; i++) {
            for (int j = 0; j < vox_size.y; j++) {
                for (int k = 0; k < vox_size.z; k++) {
                    set_octree_data.x = voxels[vox_index];
                    byte3 node_position = (byte3) { i, j, k };
                    set_octree_voxel_final(&chunkOctree, &node_position, &set_octree_data, 0);
                    vox_index++;
                }
            }
        }
        optimize_solid_nodes(&chunkOctree);
        close_same_nodes(&chunkOctree);
        ecs_set(world, e, ChunkOctree, { chunkOctree.value, chunkOctree.nodes });
        ecs_set(world, e, ChunkSize, { vox->chunks[0].size.xyz });
    #else
        ChunkSize chunkSize = { vox->chunks[0].size.xyz };
        int voxels_length = chunkSize.value.x * chunkSize.value.y * chunkSize.value.z;
        ChunkData chunk = { };
        ColorRGBs colorRGBs = { };
        int colors_length = vox->palette.values_length;
        initialize_memory_component_non_pointer(chunk, unsigned char, voxels_length);
        initialize_memory_component_non_pointer(colorRGBs, color_rgb, colors_length);
        memcpy(chunk.value, vox->chunks[0].xyzi.voxels, voxels_length);     // this lags it hard...
        memcpy(colorRGBs.value, vox->palette.values_rgb, colors_length * sizeof(color_rgb));
        ecs_set(world, e, ChunkSize, { chunkSize.value });
        ecs_set(world, e, ChunkData, { chunk.length, chunk.value });
        ecs_set(world, e, ColorRGBs, { colorRGBs.length, colorRGBs.value });
    #endif
}

ecs_entity_t spawn_vox(ecs_world_t *world, vox_file *vox, float3 position, unsigned char division) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_vox);
    zox_set(e, Position3D, { position })
    zox_set(e, ChunkDivision, { division })
    set_vox_from_vox_file(world, e, vox);
    spawn_gpu_colors(world, e);
    ecs_defer_end(world);
    return e;
}

void test_voxes(ecs_world_t *world, float3 position) {
    vox_file vox = vox_files[3];
    spawn_vox(world, &vox, (float3) { position.x - 3, position.y, position.z + 1 }, 4);
    spawn_vox(world, &vox, (float3) { position.x - 1.5f, position.y, position.z + 1 }, 3);
    spawn_vox(world, &vox, (float3) { position.x, position.y, position.z + 1 }, 2);
    spawn_vox(world, &vox, (float3) { position.x + 1.5f, position.y, position.z + 1 }, 1);
    spawn_vox(world, &vox, (float3) { position.x + 3, position.y, position.z + 1 }, 0);
}

/*ecs_entity_t spawn_vox_from_file(ecs_world_t *world, vox_file *vox, float3 position, float4 rotation, float scale) {
    ecs_defer_begin(world);
    ecs_entity_t e = spawn_chunk(world, prefab_vox, position, scale);
    set_vox_from_vox_file(world, e, vox);
    ecs_set(world, e, Rotation3D, { rotation });
    float4 rotationer = quaternion_from_euler( (float3) { 0, 0.2f * degreesToRadians, 0 });
    zox_set(e, EternalRotation, { rotationer });
    ecs_defer_end(world);
    return e;
}*/