ecs_entity_t prefab_vox;
const unsigned char max_octree_depth_character = 5; // issue with this...!
// how to control scale? VoxScale?

ecs_entity_t spawn_prefab_vox(ecs_world_t *world) {
    zox_prefab_child(prefab_chunk)
    zox_prefab_name("prefab_vox")
    zox_add_tag(e, Vox)
    // zox_prefab_set(e, Scale1D, { 1.0f })
    zox_prefab_set(e, VoxScale, { vox_model_scale })
    // because we set the data on spawn, no need to generate here
    zox_prefab_set(e, GenerateChunk, { 0 })
    zox_prefab_set(e, ChunkDirty, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    add_chunk_colors(world, e);
    add_gpu_colors(world, e);
    prefab_vox = e;
    return e;
}

unsigned char is_vox_valid(const vox_file *vox) {
    return (vox && vox->chunks);
}

void set_as_debug_vox(ecs_world_t *world, const ecs_entity_t e) {
    ColorRGBs *colorRGBs = zox_get_mut(e, ColorRGBs)
    resize_memory_component(ColorRGBs, colorRGBs, color_rgb, 1)
    colorRGBs->value[0] = (color_rgb) { 223, 239, 2 };
    zox_modified(e, ColorRGBs)
    zox_set(e, ChunkSize, { { 1, 1, 1 } })
    ChunkOctree *chunkOctree = zox_get_mut(e, ChunkOctree)
    fill_new_octree(chunkOctree, 1, 1);
    zox_modified(e, ChunkOctree)
}

void set_colors_from_vox_file(ecs_world_t *world, const ecs_entity_t e, const vox_file *vox) {
    if (!vox) return;
    int colors_length = vox->palette.values_length;
    ColorRGBs *colorRGBs = zox_get_mut(e, ColorRGBs)
    resize_memory_component(ColorRGBs, colorRGBs, color_rgb, colors_length)
    memcpy(colorRGBs->value, vox->palette.values_rgb, colors_length * sizeof(color_rgb));
    zox_modified(e, ColorRGBs)
}

void set_vox_from_vox_file(ecs_world_t *world, const ecs_entity_t e, const vox_file *vox) {
#ifdef zox_disable_set_vox
    return;
#endif
    if (!is_vox_valid(vox)) {
        set_as_debug_vox(world, e);
        return;
    }
    const unsigned char target_depth = max_octree_depth_character;
    const unsigned char *voxels = vox->chunks[0].xyzi.voxels;
    const byte3 vox_size_original = int3_to_byte3(vox->chunks[0].size.xyz);
    // maxed based on octree size
    const int max_length = pow(2, max_octree_depth_character);
    int3 vox_size = vox->chunks[0].size.xyz;
    if (vox_size.x >= max_length) vox_size.x = max_length - 1;
    if (vox_size.y >= max_length) vox_size.y = max_length - 1;
    if (vox_size.z >= max_length) vox_size.z = max_length - 1;
    ChunkOctree *chunkOctree = zox_get_mut(e, ChunkOctree)
    fill_new_octree(chunkOctree, 0, target_depth);
    byte2 set_octree_data = (byte2) { 1, max_octree_depth_character };
    byte3 position;
    int vox_index;
    for (position.x = 0; position.x < vox_size.x; position.x++) {
        for (position.y = 0; position.y < vox_size.y; position.y++) {
            for (position.z = 0; position.z < vox_size.z; position.z++) {
                vox_index = byte3_array_index(position, vox_size_original);
                set_octree_data.x = voxels[vox_index];
                byte3 node_position = position;
                set_octree_voxel_final(chunkOctree, &node_position, &set_octree_data, 0);
            }
        }
    }
    optimize_solid_nodes(chunkOctree);
    close_same_nodes(chunkOctree);
    zox_modified(e, ChunkOctree)
    zox_set(e, ChunkSize, { vox_size }) // size
    set_colors_from_vox_file(world, e, vox); // colors
}

ecs_entity_t spawn_vox(ecs_world_t *world, const vox_file *vox, const float3 position, const unsigned char division) {
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

// byte3 offset = (byte3) { (32 - vox_size.x) / 2, (32 - vox_size.y) / 2, (32 - vox_size.z) / 2 };
// zoxel_log(" > setting vox [%ix%ix%i] - offset [%ix%ix%i]\n", vox_size.x, vox_size.y, vox_size.z, offset.x, offset.y, offset.z);

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
