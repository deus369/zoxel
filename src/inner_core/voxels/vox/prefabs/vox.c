ecs_entity_t prefab_vox;

ecs_entity_t spawn_prefab_vox(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_vox");
    zoxel_set(world, e, GenerateChunk, { 0 });
    zoxel_set(world, e, ChunkDirty, { 1 });
    // zoxel_set(world, e, EternalRotation, { { 0, 0, 0, 0 } });
    zoxel_add(world, e, Colors);
    if (!headless) {
        zoxel_add(world, e, MeshColors);
    }
    ecs_defer_end(world);
    prefab_vox = e;
    return e;
}

void set_vox_from_vox_file(ecs_world_t *world, ecs_entity_t e, vox_file *vox) {
    ChunkSize chunkSize = { vox->chunks[0].size.xyz };
    int voxels_length = chunkSize.value.x * chunkSize.value.y * chunkSize.value.z;
    ChunkData chunk = { };
    Colors colors = { };
    int colors_length = vox->palette.chunk_content / 4;
    initialize_memory_component_non_pointer(chunk, unsigned char, voxels_length);
    initialize_memory_component_non_pointer(colors, color, colors_length);
    memcpy(chunk.value, vox->chunks[0].xyzi.voxels, voxels_length);
    memcpy(colors.value, vox->palette.values, colors_length * 4);
    ecs_set(world, e, ChunkSize, { chunkSize.value });
    ecs_set(world, e, ChunkData, { chunk.length, chunk.value });
    ecs_set(world, e, Colors, { colors.length, colors.value });
}

ecs_entity_t spawn_vox_from_file(ecs_world_t *world, vox_file *vox, float3 position, float4 rotation, float scale) {
    ecs_defer_begin(world);
    ecs_entity_t e = spawn_voxel_chunk_mesh(world, prefab_vox, position, scale);
    set_vox_from_vox_file(world, e, vox);
    ecs_set(world, e, Rotation3D, { rotation });
    float4 rotationer = quaternion_from_euler( (float3) { 0, 0.2f * degreesToRadians, 0 });
    zoxel_set(world, e, EternalRotation, { rotationer });
    ecs_defer_end(world);
    return e;
}