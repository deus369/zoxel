// GenerateVox == 1
const unsigned char is_generate_vox_airs = 1;
const unsigned char is_generate_vox_outlines = 1;

void noise_vox(ChunkOctree *chunk, const byte3 size, const unsigned char is_generate_vox_outlines, const byte2 set_voxel_1, const byte2 set_voxel_2, const byte2 set_voxel_3, const byte2 set_voxel_black, const byte2 set_voxel_air) {
    byte3 voxel_position;
    for (voxel_position.x = 0; voxel_position.x < size.x; voxel_position.x++) {
        for (voxel_position.y = 0; voxel_position.y < size.y; voxel_position.y++) {
            for (voxel_position.z = 0; voxel_position.z < size.z; voxel_position.z++) {
                byte2 set_voxel;
                unsigned char did_set_outline = 0;
                if (is_generate_vox_outlines) {
                    unsigned char on_edges = byte3_on_edges(voxel_position, size);
                    if (on_edges) {
                        set_voxel = set_voxel_black;
                        did_set_outline = 1;
                    }
                }
                if (!did_set_outline) {
                    const int rando = rand() % 1000;
                    if (rando <= 150) {
                        const unsigned char on_edge = byte3_on_edge(voxel_position, size);
                        if (!on_edge) set_voxel = set_voxel_1;
                        else set_voxel = set_voxel_air;
                    } else if (rando <= 300) set_voxel = set_voxel_3;
                    else if (rando <= 450) set_voxel = set_voxel_2;
                    else set_voxel = set_voxel_1;
                }
                byte3 node_position = voxel_position;
                set_octree_voxel(chunk, &node_position, &set_voxel, 0);
            }
        }
    }
}

void GenerateVoxSystem(ecs_iter_t *it) {
    // zox_change_check()
    const unsigned char target_depth = max_octree_depth;
    const unsigned char chunk_voxel_length = powers_of_two_byte[target_depth];
    zox_iter_world()
    zox_field_in(Color, colors, 1)
    zox_field_out(GenerateVox, generateVoxs, 2)
    zox_field_out(ChunkOctree, chunkOctrees, 3)
    zox_field_out(ColorRGBs, colorRGBss, 4)
    // zox_field_out(ChunkDirty, chunkDirtys, 5) // for now we don't use this, some models have no dirty / just have data
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateVox, generateVoxs, generateVox)
        if (!generateVox->value) continue;
        // zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        // if (chunkDirty->value) continue;
        zox_field_e()
        zox_field_i(Color, colors, color2)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_o(ColorRGBs, colorRGBss, colorRGBs)
        const unsigned char colors_count = 3 + is_generate_vox_outlines;
        resize_memory_component(ColorRGBs, colorRGBs, color_rgb, colors_count)
        const color_rgb color_rgb_2 = color_to_color_rgb(color2->value);
        colorRGBs->value[0] = color_rgb_2;
        colorRGBs->value[1] = color_rgb_2;
        colorRGBs->value[2] = color_rgb_2;
        color_rgb_multiply_float(&colorRGBs->value[1], 0.7f);
        color_rgb_multiply_float(&colorRGBs->value[2], 1.2f);
        if (is_generate_vox_outlines) colorRGBs->value[3] = (color_rgb) { 5, 5, 5 };
        const byte2 set_voxel_1 = (byte2) { 1, target_depth };
        const byte2 set_voxel_2 = (byte2) { 2, target_depth };
        const byte2 set_voxel_3 = (byte2) { 3, target_depth };
        const byte2 set_voxel_air = (byte2) { !is_generate_vox_airs, target_depth };
        const byte2 set_voxel_black = (byte2) { 4, target_depth };
        fill_new_octree(chunkOctree, 0, target_depth);
        byte3 voxel_position;
        byte3 size = (byte3) { chunk_voxel_length, chunk_voxel_length, chunk_voxel_length };
        if (zox_has(e, VoxRubble)) {
            const int rubble_count = 200;
            for (int j = 0; j < rubble_count; j++) {
                // randomly place
                voxel_position.x = rand() % size.x;
                voxel_position.z = rand() % size.y;
                // voxel_position.y = rand() % size.z;
                for (int k = 0; k < size.y; k++) {
                    voxel_position.y = k;
                    byte3 node_position = voxel_position;
                    if (get_octree_voxel(chunkOctree, &node_position, target_depth) == 0) break;
                }
                int rando = rand() % 1000;
                byte2 set_voxel = set_voxel_1;
                if (rando <= 222) set_voxel = set_voxel_2;
                else if (rando <= 444) set_voxel = set_voxel_3;
                byte3 node_position = voxel_position;
                set_octree_voxel(chunkOctree, &node_position, &set_voxel, 0);
            }
        } else {
            noise_vox(chunkOctree, size, is_generate_vox_outlines, set_voxel_1, set_voxel_2, set_voxel_3, set_voxel_black, set_voxel_air);
            /*for (voxel_position.x = 0; voxel_position.x < size.x; voxel_position.x++) {
                for (voxel_position.y = 0; voxel_position.y < size.y; voxel_position.y++) {
                    for (voxel_position.z = 0; voxel_position.z < size.z; voxel_position.z++) {
                        byte2 set_voxel;
                        unsigned char did_set_outline = 0;
                        if (is_generate_vox_outlines) {
                            unsigned char on_edges = byte3_on_edges(voxel_position, size);
                            if (on_edges) {
                                set_voxel = set_voxel_black;
                                did_set_outline = 1;
                            }
                        }
                        if (!did_set_outline) {
                            const int rando = rand() % 1000;
                            if (rando <= 150) {
                                const unsigned char on_edge = byte3_on_edge(voxel_position, size);
                                if (!on_edge) set_voxel = set_voxel_1;
                                else set_voxel = set_voxel_air;
                            } else if (rando <= 300) set_voxel = set_voxel_3;
                            else if (rando <= 450) set_voxel = set_voxel_2;
                            else set_voxel = set_voxel_1;
                        }
                        byte3 node_position = voxel_position;
                        set_octree_voxel(chunkOctree, &node_position, &set_voxel, 0);
                    }
                }
            }*/
            if (zox_has(e, BlendVox)) {
                const int grass_random = 6;
                const int grass_position = chunk_voxel_length - chunk_voxel_length / 3;
                const color under_color = zox_get_value(e, SecondaryColor)
                color_rgb color_4 = color_to_color_rgb(under_color);
                color_rgb color_5 = color_4;
                color_rgb_multiply_float(&color_5, 0.7f);
                color_rgb color_6 = color_4;
                color_rgb_multiply_float(&color_6, 1.2f);
                add_to_ColorRGBs(colorRGBs, color_4);
                add_to_ColorRGBs(colorRGBs, color_5);
                add_to_ColorRGBs(colorRGBs, color_6);
                byte2 set_voxel_4 = (byte2) { colors_count + 1, target_depth };
                byte2 set_voxel_5 = (byte2) { colors_count + 2, target_depth };
                byte2 set_voxel_6 = (byte2) { colors_count + 3, target_depth };
                for (voxel_position.x = 0; voxel_position.x < size.x; voxel_position.x++) {
                    for (voxel_position.z = 0; voxel_position.z < size.z; voxel_position.z++) {
                        int height = grass_position - rand() % grass_random;
                        for (voxel_position.y = 0; voxel_position.y < height; voxel_position.y++) {
                            byte2 set_voxel;
                            unsigned char did_set_outline = 0;
                            if (is_generate_vox_outlines) {
                                unsigned char on_edges = byte3_on_edges(voxel_position, size);
                                if (on_edges) {
                                    set_voxel = set_voxel_black;
                                    did_set_outline = 1;
                                }
                            }
                            if (!did_set_outline) {
                                int rando = rand() % 1000;
                                if (rando <= 150) {
                                    if (byte3_on_edge(voxel_position, size)) set_voxel = set_voxel_air;
                                    else set_voxel = set_voxel_5;
                                } else if (rando <= 300) set_voxel = set_voxel_6;
                                else set_voxel = set_voxel_4;
                            }
                            byte3 node_position = voxel_position;
                            set_octree_voxel(chunkOctree, &node_position, &set_voxel, 0);
                        }
                    }
                }
            }
        }
#ifndef zox_disable_closing_octree_nodes
        close_same_nodes(chunkOctree);
#endif
        generateVox->value = 0;
        // chunkDirty->value = 1;
    }
} zox_declare_system(GenerateVoxSystem)

// testing
/*if (voxel_position.x >= chunk_voxel_length / 2) set_voxel = set_voxel_1;
else set_voxel = set_voxel_2;*/
