// GenerateVox == 1
const unsigned char is_generate_vox_airs = 0;

unsigned char byte3_on_edge(const byte3 pos, const byte3 size) {
    return pos.x == 0 || pos.y == 0 || pos.z == 0 || pos.x == size.x - 1 || pos.y == size.y - 1 || pos.z == size.z - 1;
}

void GenerateVoxSystem(ecs_iter_t *it) {
    // zox_change_check()
    const unsigned char target_depth = max_octree_depth;
    const unsigned char chunk_voxel_length = powers_of_two_byte[target_depth];
    const float2 map_size_f = (float2) { chunk_voxel_length, chunk_voxel_length };
    zox_field_in(Color, colors, 1)
    zox_field_out(GenerateVox, generateVoxs, 2)
    zox_field_out(ChunkOctree, chunkOctrees, 3)
    zox_field_out(ColorRGBs, colorRGBss, 4)
    zox_field_out(ChunkDirty, chunkDirtys, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateVox, generateVoxs, generateVox)
        if (!generateVox->value) continue;
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value) continue;
        zox_field_i(Color, colors, color)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_o(ColorRGBs, colorRGBss, colorRGBs)
        resize_memory_component(ColorRGBs, colorRGBs, color_rgb, 3)
        const color_rgb color_rgb_2 = color_to_color_rgb(color->value);
        colorRGBs->value[0] = color_rgb_2;
        colorRGBs->value[1] = color_rgb_2;
        colorRGBs->value[2] = color_rgb_2;
        color_rgb_multiply_float(&colorRGBs->value[1], 0.7f);
        color_rgb_multiply_float(&colorRGBs->value[2], 1.2f);
        // colorRGBs->value[0] = (color_rgb) { 96, 51, 16 };
        // colorRGBs->value[1] = (color_rgb) { 68, 45, 27 };
        // colorRGBs->value[2] = (color_rgb) { 14, 7, 3 };
        const byte2 set_voxel_1 = (byte2) { 1, target_depth };
        const byte2 set_voxel_2 = (byte2) { 2, target_depth };
        const byte2 set_voxel_3 = (byte2) { 3, target_depth };
        const byte2 set_voxel_air = (byte2) { !is_generate_vox_airs, target_depth };
        fill_new_octree(chunkOctree, 0, target_depth);
        byte3 voxel_position;
        byte3 size = (byte3) { chunk_voxel_length, chunk_voxel_length, chunk_voxel_length };
        for (voxel_position.x = 0; voxel_position.x < chunk_voxel_length; voxel_position.x++) {
            for (voxel_position.y = 0; voxel_position.y < chunk_voxel_length; voxel_position.y++) {
                for (voxel_position.z = 0; voxel_position.z < chunk_voxel_length; voxel_position.z++) {
                    byte2 set_voxel;
                    int rando = rand() % 1000;
                    if (rando <= 150) set_voxel = set_voxel_1;
                    else if (rando <= 300) set_voxel = set_voxel_3;
                    else if (rando <= 450) set_voxel = set_voxel_2;
                    else set_voxel = set_voxel_1;
                    if (byte3_on_edge(voxel_position, size) && rando <= 150) set_voxel = set_voxel_air;
                    byte3 node_position = voxel_position;
                    set_octree_voxel(chunkOctree, &node_position, &set_voxel, 0);
                }
            }
        }
#ifndef zox_disable_closing_octree_nodes
        close_same_nodes(chunkOctree);
#endif
        generateVox->value = 0;
        chunkDirty->value = 1;
        /*zox_log(" +  GenerateVoxSystem::\n")
        zox_log("   +  color_rgb_2: - %xx%xx%x\n", color_rgb_2.r, color_rgb_2.g, color_rgb_2.b)
        zox_log("   +  c1: - %xx%xx%x\n", colorRGBs->value[0].r, colorRGBs->value[0].g, colorRGBs->value[0].b)
        zox_log("   +  c2: - %xx%xx%x\n", colorRGBs->value[1].r, colorRGBs->value[1].g, colorRGBs->value[1].b)*/
    }
} zox_declare_system(GenerateVoxSystem)
