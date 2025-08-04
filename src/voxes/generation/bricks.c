void build_vox_bricks(
    VoxelNode *node,
    const byte node_depth,
    const byte2 color_range,
    const byte black_voxel
) {
    const byte size_whole = powers_of_two_byte[node_depth];
    byte3 size = byte3_single(size_whole);
    byte3 pos;

    // parameters you can tweak
    const byte brick_w     = 8;
    const byte brick_h     = 4;
    const byte brick_d     = 8;
    const byte mortar      = 1;
    const byte chip_chance = 5; // percent

    for (pos.y = 0; pos.y < size.y; pos.y++) {
        // which “row” of bricks am I in?
        byte row = pos.y / (brick_h + mortar);
        bool stagger = row & 1;  // every other row is offset

        for (pos.x = 0; pos.x < size.x; pos.x++) {
            // compute x with stagger
            int sx = pos.x + (stagger ? (brick_w/2 + mortar) : 0);

            for (pos.z = 0; pos.z < size.z; pos.z++) {
                // brick mask
                bool in_x = (sx % (brick_w + mortar)) < brick_w;
                bool in_y = (pos.y % (brick_h + mortar)) < brick_h;
                bool in_z = (pos.z % (brick_d + mortar)) < brick_d;

                if (in_x && in_y && in_z) {
                    // random chip at edges
                    bool chip = (rand() % 100) < chip_chance
                    && (
                        (sx % (brick_w + mortar) < 2) ||
                        (sx % (brick_w + mortar) >= brick_w-2) ||
                        (pos.z % (brick_d + mortar) < 1) ||
                        (pos.z % (brick_d + mortar) >= brick_d-1)
                    );
                    if (chip) {
                        set_voxelc(node, node_depth, pos, black_voxel, 0);
                    } else {
                        byte c = color_range.x + rand() % (color_range.y - color_range.x);
                        set_voxelc(node, node_depth, pos, c, 0);
                    }
                } else {
                    // mortar
                    set_voxelc(node, node_depth, pos, black_voxel, 0);
                }
            }
        }
    }
}
