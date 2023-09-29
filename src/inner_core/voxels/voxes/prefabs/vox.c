ecs_entity_t prefab_vox;
const unsigned char max_octree_depth_character = 5;

ecs_entity_t spawn_prefab_vox(ecs_world_t *world) {
    zox_prefab_child(prefab_chunk)
    zox_prefab_name("prefab_vox")
    add_chunk_colors(world, e);
    zox_prefab_set(e, Scale1D, { 1.0f })
    // because we set the data on spawn, no need to generate here
    zox_prefab_set(e, GenerateChunk, { 0 })
    zox_prefab_set(e, ChunkDirty, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    add_gpu_colors(world, e);
    prefab_vox = e;
    return e;
}

void set_vox_from_vox_file(ecs_world_t *world, ecs_entity_t e, const vox_file *vox) {
    #ifdef zox_disable_set_vox
        return;
    #endif
    #ifndef zox_disable_vox_octrees
        unsigned char target_depth = max_octree_depth_character;
        int3 vox_size = vox->chunks[0].size.xyz;
        unsigned char *voxels = vox->chunks[0].xyzi.voxels;
        // zoxel_log(" > setting vox [%ix%ix%i]\n", vox_size.x, vox_size.y, vox_size.z);
        int colors_length = vox->palette.values_length;
        ColorRGBs *colorRGBs = ecs_get_mut(world, e, ColorRGBs);
        ChunkOctree *chunkOctree = ecs_get_mut(world, e, ChunkOctree);
        resize_memory_component(ColorRGBs, colorRGBs, color_rgb, colors_length)
        memcpy(colorRGBs->value, vox->palette.values_rgb, colors_length * sizeof(color_rgb));
        // ChunkOctree chunkOctree = { };
        fill_new_octree(chunkOctree, 0, target_depth);
        byte2 set_octree_data = (byte2) { 1, max_octree_depth_character };
        int vox_index = 0;
        // byte3 offset = (byte3) { (32 - vox_size.x) / 2, (32 - vox_size.y) / 2, (32 - vox_size.z) / 2 };
        //zoxel_log(" > setting vox [%ix%ix%i] - offset [%ix%ix%i]\n", vox_size.x, vox_size.y, vox_size.z, offset.x, offset.y, offset.z);
        for (int i = 0; i < vox_size.x; i++) {
            for (int j = 0; j < vox_size.y; j++) {
                for (int k = 0; k < vox_size.z; k++) {
                    set_octree_data.x = voxels[vox_index];
                    byte3 node_position = (byte3) { i, j, k };
                    // byte3_add_byte3_p(&node_position, offset);
                    set_octree_voxel_final(chunkOctree, &node_position, &set_octree_data, 0);
                    vox_index++;
                }
            }
        }
        optimize_solid_nodes(chunkOctree);
        close_same_nodes(chunkOctree);
        ecs_modified(world, e, ColorRGBs);
        ecs_modified(world, e, ChunkOctree);
        zox_set(e, ChunkSize, { vox_size })
        // zox_set(e, ChunkOctree, { chunkOctree.value, chunkOctree.nodes })
    #else
        /*ChunkSize chunkSize = { vox->chunks[0].size.xyz };
        int voxels_length = chunkSize.value.x * chunkSize.value.y * chunkSize.value.z;
        ChunkData chunk = { };
        ColorRGBs colorRGBs = { };
        int colors_length = vox->palette.values_length;
        initialize_memory_component_non_pointer(chunk, unsigned char, voxels_length)
        initialize_memory_component_non_pointer(colorRGBs, color_rgb, colors_length)
        memcpy(chunk.value, vox->chunks[0].xyzi.voxels, voxels_length);     // this lags it hard...
        memcpy(colorRGBs.value, vox->palette.values_rgb, colors_length * sizeof(color_rgb));
        zox_set(e, ChunkSize, { chunkSize.value })
        zox_set(e, ChunkData, { chunk.length, chunk.value })
        zox_set(e, ColorRGBs, { colorRGBs.length, colorRGBs.value })*/
    #endif
}

ecs_entity_t spawn_vox(ecs_world_t *world, vox_file *vox, float3 position, unsigned char division) {
    zox_instance(prefab_vox)
    zox_prefab_set(e, Position3D, { position })
    zox_prefab_set(e, RenderLod, { division })
    set_vox_from_vox_file(world, e, vox);
    spawn_gpu_colors(world, e);
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