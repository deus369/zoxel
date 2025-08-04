void build_vox_rubble(VoxelNode *node,
    const byte node_depth,
    const byte2 voxel_range,
    const int rubble_count,
    const byte rubble_height)
{
    fill_new_octree(node, 0, node_depth);  // clear chunk
    const byte length = powers_of_two_byte[node_depth];
    byte3 position;
    for (int j = 0; j < rubble_count; j++) {
        position.x = rand() % length;
        position.z = rand() % length;
        for (int k = 0; k < length; k++) {
            position.y = k;
            byte3 node_position = position;
            if (get_sub_node_voxel(node, &node_position, node_depth) == 0) {
                break;
            }
        }
        if (position.y > rubble_height) {
            continue;
        }
        byte value = voxel_range.x + rand() % (voxel_range.y - voxel_range.x);
        // byte2 set_voxel = (byte2) { voxel, node_depth };
        // byte3 node_position = position;
        // set_octree_voxel(node, &node_position, &set_voxel, 0);

        set_voxelc(
            node,
            node_depth,
            position,
            value,
            0);
    }
}