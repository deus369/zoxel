define_fun_stopwatch(time_set_vox, 0);

void set_colors_from_vox_file(ecs_world_t *world,
    const ecs_entity_t e,
    const vox_file *vox)
{
    if (!vox) {
        return;
    }
    int colors_length = vox->palette.values_length;
    ColorRGBs *colorRGBs = zox_get_mut(e, ColorRGBs)
    resize_memory_component(ColorRGBs, colorRGBs, color_rgb, colors_length)
    memcpy(colorRGBs->value, vox->palette.values_rgb, colors_length * sizeof(color_rgb));
    zox_modified(e, ColorRGBs)
}

void set_as_debug_vox(ecs_world_t *world, const ecs_entity_t e) {
    ColorRGBs *colorRGBs = zox_get_mut(e, ColorRGBs)
    resize_memory_component(ColorRGBs, colorRGBs, color_rgb, 1)
    colorRGBs->value[0] = (color_rgb) { 223, 239, 2 };
    zox_modified(e, ColorRGBs)
    zox_set(e, ChunkSize, { { 1, 1, 1 } })
    VoxelNode *voxelNode = zox_get_mut(e, VoxelNode)
    fill_new_octree(voxelNode, 1, 1);
    zox_modified(e, VoxelNode)
}

byte is_vox_valid(const vox_file *vox) {
    return (vox && vox->chunks);
}

void set_vox_file(ecs_world_t *world,
    const ecs_entity_t e,
    const vox_file* vox)
{
    if (!is_vox_valid(vox)) {
        set_as_debug_vox(world, e);
        return;
    }
    startwatch(time_set_vox);

    const byte node_depth = character_depth;
    zox_set(e, NodeDepth, { node_depth })
    const byte *voxels = vox->chunks[0].xyzi.voxels;
    const byte3 vox_size_original = int3_to_byte3(vox->chunks[0].size.xyz);
    const int max_length = pow(2, node_depth);
    int3 vox_size = vox->chunks[0].size.xyz;
    if (vox_size.x > max_length) {
        vox_size.x = max_length;
    }
    if (vox_size.y > max_length) {
        vox_size.y = max_length;
    }
    if (vox_size.z > max_length) {
        vox_size.z = max_length;
    }
    zox_set(e, ChunkSize, { vox_size }) // size

    zox_muter(e, VoxelNode, node)
    fill_new_octree(node, 0, node_depth);
    tapwatch(time_set_vox, "fill_new_octree");

    byte2 data = (byte2) {
        1,
        node_depth
    };
    byte3 position;
    int vox_index;
    for (position.x = 0; position.x < vox_size.x; position.x++) {
        for (position.y = 0; position.y < vox_size.y; position.y++) {
            for (position.z = 0; position.z < vox_size.z; position.z++) {
                vox_index = byte3_array_index(position, vox_size_original);
                if (!voxels[vox_index]) {
                    continue;
                }
                data.x = voxels[vox_index];
                byte3 node_position = position;
                set_octree_voxel_final(node, &node_position, data, 0);
            }
        }
    }
    tapwatch(time_set_vox, "set_voxel_node");

    optimize_solid_nodes(node);
    tapwatch(time_set_vox, "optimize_solid_nodes");

    reduce_voxel_nodes(world, node);
    tapwatch(time_set_vox, "reduce_voxel_nodes");

    set_colors_from_vox_file(world, e, vox); // colors
    tapwatch(time_set_vox, "set_colors_from_vox_file");

    endwatch(time_set_vox, "set_vox_data");
}