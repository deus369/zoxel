// uses chunk above for air check
// chunk_above used purely for top of chunk checks
byte3 find_position_on_ground(
    const VoxelNode *chunk,
    const VoxelNode *chunk_above,
    const byte depth,
    const byte2 positionxz)
{
    if (chunk == NULL) {
        return byte3_full;
    }
    const byte length = powers_of_two_byte[depth];
    byte checks_count = 0;
    byte3 position = (byte3) {
        positionxz.x,
        0,
        positionxz.y
    };
    // find ground from tallest point
    // special case for top of chunks
    if (chunk_above) {
        byte3 temp1 = position;
        byte3 temp2 = (byte3) {
            position.x,
            length - 1,
            position.z
        };
        const byte voxel_up = get_sub_node_voxel(chunk_above, &temp1, depth);
        const byte voxel_down = get_sub_node_voxel(chunk, &temp2, depth);
        if (!voxel_up && voxel_down) { // can stand on voxel
            position.y = length;
            return position;
        }
    }
    for (position.y = length - 1; position.y >= 1; position.y--)
    {
        byte3 temp3 = position;
        byte3 temp4 = (byte3) { position.x, position.y - 1, position.z };
        const byte voxel_up = get_sub_node_voxel(chunk, &temp3, depth);
        const byte voxel_down = get_sub_node_voxel(chunk, &temp4, depth);
        if (!voxel_up && voxel_down) { // can stand on voxel
            return position;
        }
    }
    return byte3_full;
}


byte3 find_random_position_on_ground(
    const VoxelNode *chunk,
    const VoxelNode *chunk_above,
    const byte depth)
{
    const byte length = powers_of_two_byte[depth];
    byte checks_count = 0;
    byte3 position = byte3_full;
    while (checks_count < max_position_checks) {
        byte2 positionxz = (byte2) { rand() % length, rand() % length };
        byte3 position = find_position_on_ground(
            chunk,
            chunk_above,
            depth,
            positionxz);
        if (!byte3_equals(position, byte3_full)) {
            return position;
        }
        checks_count++;
    }
    return byte3_full;
}