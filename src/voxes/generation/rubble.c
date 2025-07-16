void build_vox_rubble(VoxelNode *voxelNode,
    const byte node_depth,
    const byte2 voxel_range,
    const int rubble_count,
    const byte rubble_height)
{
    fill_new_octree(voxelNode, 0, node_depth);  // clear chunk
    const byte length = powers_of_two_byte[node_depth];
    byte3 voxel_position;
    for (int j = 0; j < rubble_count; j++) {
        voxel_position.x = rand() % length;
        voxel_position.z = rand() % length;
        for (int k = 0; k < length; k++) {
            voxel_position.y = k;
            byte3 node_position = voxel_position;
            if (get_sub_node_voxel(voxelNode, &node_position, node_depth) == 0) {
                break;
            }
        }
        if (voxel_position.y > rubble_height) {
            continue;
        }
        byte voxel = voxel_range.x + rand() % (voxel_range.y - voxel_range.x);
        byte2 set_voxel = (byte2) { voxel, node_depth };
        byte3 node_position = voxel_position;
        set_octree_voxel(voxelNode, &node_position, &set_voxel, 0);
    }
}