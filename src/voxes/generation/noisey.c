void build_vox_noisey(VoxelNode *voxelNode,
    const byte node_depth,
    const byte2 voxel_range,
    const byte black_voxel)
{
    const byte length = powers_of_two_byte[node_depth];
    byte3 size = byte3_single(length);
    byte3 voxel_position;
    for (voxel_position.x = 0; voxel_position.x < size.x; voxel_position.x++) {
        for (voxel_position.y = 0; voxel_position.y < size.y; voxel_position.y++) {
            for (voxel_position.z = 0; voxel_position.z < size.z; voxel_position.z++) {
                byte3 temp_position = voxel_position;
                if (get_sub_node_voxel(voxelNode, &temp_position, node_depth) == black_voxel) {
                    continue;
                }
                const int rando = rand() % 1000;
                if (rando > 300) {
                    continue;
                }
                const byte voxel = voxel_range.x + rand() % (voxel_range.y - voxel_range.x);
                byte2 set_voxel = (byte2) { voxel, node_depth };
                byte3 node_position = voxel_position;
                set_octree_voxel(voxelNode, &node_position, &set_voxel, 0);
            }
        }
    }
}