ecs_entity_t prefab_vox;

ecs_entity_t spawn_prefab_vox(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "prefab_vox");
    zoxel_add(world, e, MeshColors);
    zoxel_set(world, e, GenerateChunk, { 0 });
    zoxel_set(world, e, ChunkDirty, { 1 });
    zoxel_add(world, e, EternalRotation);
    zoxel_add(world, e, Colors);
    ecs_defer_end(world);
    prefab_vox = e;
    return e;
}

ecs_entity_t spawn_vox_from_file(ecs_world_t *world, vox_file *vox, float3 position, float4 rotation, float scale)
{
    ecs_defer_begin(world);
    ecs_entity_t e = spawn_voxel_chunk_mesh(world, prefab_vox, position, scale);
    ecs_set(world, e, Rotation, { rotation });
    ChunkSize chunkSize = { vox->chunks[0].size.xyz };
    ecs_set(world, e, ChunkSize, { chunkSize.value });
    int voxels_length = chunkSize.value.x * chunkSize.value.y * chunkSize.value.z;
    Chunk chunk = { };
    initialize_memory_component_non_pointer(chunk, unsigned char, voxels_length);
    memcpy(chunk.value, vox->chunks[0].xyzi.voxels, voxels_length);
    ecs_set(world, e, Chunk, { chunk.length, chunk.value });
    // set colors on vox
    int colors_length = vox->palette.chunk_content / 4;
    Colors colors = { };
    initialize_memory_component_non_pointer(colors, color, colors_length);
    for (int i = 0; i < colors_length; i++)
    {
        colors.value[i] = vox->palette.values[i];
    }
    // memcpy(colors.value, vox->palette.values, colors_length);
    ecs_set(world, e, Colors, { colors.length, colors.value });
    float4 rotationer = quaternion_from_euler( (float3) { 0, 0.2f * degreesToRadians, 0 });
    zoxel_set(world, e, EternalRotation, { rotationer });
    ecs_defer_end(world);
    return e;
}