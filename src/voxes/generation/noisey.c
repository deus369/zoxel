void vnoise3(VoxelNode *node,
    const byte node_depth,
    const byte2 voxel_range,
    const byte black_voxel)
{
    const byte length = powers_of_two_byte[node_depth];
    byte3 size = byte3_single(length);
    byte3 position;
    for (position.x = 0; position.x < size.x; position.x++) {
        for (position.y = 0; position.y < size.y; position.y++) {
            for (position.z = 0; position.z < size.z; position.z++) {
                byte3 temp_position = position;
                // skip outline parts
                if (get_sub_node_voxel(node, &temp_position, node_depth) == black_voxel) {
                    continue;
                }
                /*const int rando = rand() % 1000;
                if (rando > 300) {
                    continue;
                }*/
                const byte value = voxel_range.x + rand() % (voxel_range.y - voxel_range.x);
                //byte2 set_voxel = (byte2) { voxel, node_depth };
                //byte3 node_position = position;
                //set_octree_voxel(node, &node_position, &set_voxel, 0);
                set_voxelc(
                    node,
                    node_depth,
                    position,
                    value,
                    0);
            }
        }
    }
}