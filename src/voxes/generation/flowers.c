typedef signed char sbyte;

void build_vox_flower_patch(
    VoxelNode *node,
    const byte node_depth,
    const byte2 stem_range,
    const byte2 petal_range,
    const byte black_voxel
) {
    const byte spawn_count = 4 + rand() % 8; // 32
    const byte size = powers_of_two_byte[node_depth];
    byte3 pos;
    byte3 base = byte3_zero;

    for (int i = 0; i < spawn_count; i++) {
        // random flower base
        base.x = rand() % size;
        base.y = 0; // rand() % (size / 4); // keep them grounded
        base.z = rand() % size;

        byte stem_height = 2 + rand() % 7;
        byte petal_type = rand() % 4;

        // stem
        for (byte h = 0; h < stem_height; h++) {
            pos = base;
            pos.y += h;
            byte c = stem_range.x + rand() % (stem_range.y - stem_range.x);
            set_voxelc(node, node_depth, pos, c, 0);
        }

        // petals
        pos.y = base.y + stem_height;

        byte flower_color = petal_range.x + rand() % (petal_range.y - petal_range.x);

        switch (petal_type) {
            case 0: // cross pattern
                set_voxelc(node, node_depth, pos, flower_color, 0);
                set_voxelc(node, node_depth, (byte3) {pos.x+1,pos.y,pos.z}, flower_color, 0);
                set_voxelc(node, node_depth, (byte3) {pos.x-1,pos.y,pos.z}, flower_color, 0);
                set_voxelc(node, node_depth, (byte3) {pos.x,pos.y,pos.z+1}, flower_color, 0);
                set_voxelc(node, node_depth, (byte3) {pos.x,pos.y,pos.z-1}, flower_color, 0);
                break;

            case 1: // cluster ball
                for (sbyte dx = -1; dx <= 1; dx++) {
                    for (sbyte dz = -1; dz <= 1; dz++) {
                        if (rand() % 2) {
                            byte3 petal = { pos.x + dx, pos.y, pos.z + dz };
                            set_voxelc(node, node_depth, petal, flower_color, 0);
                        }
                    }
                }
                break;

            case 2: // flat ring
                for (byte i = 0; i < 6; i++) {
                    sbyte dx = (i & 1) ? 1 : -1;
                    sbyte dz = (i & 2) ? 1 : -1;
                    byte3 ring = { pos.x + dx, pos.y, pos.z + dz };
                    set_voxelc(node, node_depth, ring, flower_color, 0);
                }
                break;

            case 3: // withered single
                set_voxelc(node, node_depth, pos, black_voxel, 0);
                break;
        }
    }
}
