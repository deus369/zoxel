

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

void set_vox_file(ecs_world_t *world, const ecs_entity_t e, const vox_file *vox) {
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
    if (vox_size.x > max_length) vox_size.x = max_length;
    if (vox_size.y > max_length) vox_size.y = max_length;
    if (vox_size.z > max_length) vox_size.z = max_length;
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

void clone_vox_data(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t source) {
    if (!source) {
        return;
    }
    const int3 chunk_size = zox_get_value(source, ChunkSize)
    zox_set(e, ChunkSize, { chunk_size })
    const ChunkOctree *chunk_octree_source = zox_get(source, ChunkOctree)
    ChunkOctree *chunk_octree_dest = zox_get_mut(e, ChunkOctree)
    clone_ChunkOctree(chunk_octree_dest, chunk_octree_source);
    zox_modified(e, ChunkOctree)
    const ColorRGBs *colors_source = zox_get(source, ColorRGBs)
    ColorRGBs *colors_dest = zox_get_mut(e, ColorRGBs)
    //clone_ColorRGBs(colors_dest, colors_source)
    colors_dest->length = colors_source->length;
    const int memory_length = sizeof(color_rgb) * colors_dest->length;
    colors_dest->value = memcpy(malloc(memory_length), colors_source->value, memory_length);
    zox_modified(e, ColorRGBs)
}
