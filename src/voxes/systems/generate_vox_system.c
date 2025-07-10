// todo: seperate out into generation functions
void GenerateVoxSystem(ecs_iter_t *it) {
    const byte unique_colors = 8;
    const int grass_random = 6;
    const byte node_depth = block_vox_depth;
    const byte chunk_voxel_length = powers_of_two_byte[node_depth];
    zox_field_world()
    zox_field_in(Color, colors, 1)
    zox_field_out(GenerateVox, generateVoxs, 2)
    zox_field_out(ChunkOctree, chunkOctrees, 3)
    zox_field_out(NodeDepth, nodeDepths, 4)
    zox_field_out(ColorRGBs, colorRGBss, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(Color, colors, color2)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_o(NodeDepth, nodeDepths, nodeDepth)
        zox_field_o(ColorRGBs, colorRGBss, colorRGBs)
        zox_field_o(GenerateVox, generateVoxs, generateVox)
        if (!generateVox->value) {
            continue;
        }
        const byte colors_count = unique_colors + is_generate_vox_outlines;
        resize_memory_component(ColorRGBs, colorRGBs, color_rgb, colors_count)
        const color_rgb color_rgb_2 = color_to_color_rgb(color2->value);
        const byte black_voxel = unique_colors + 1;
        const byte2 voxel_range = (byte2) { 1, unique_colors - 1 };
        for (int j = 0; j < unique_colors; j++) {
            colorRGBs->value[j] = color_rgb_2;
            color_rgb_multiply_float(&colorRGBs->value[j], 0.7f + 0.6f * (rand() % 100) * 0.01f);
        }
        if (is_generate_vox_outlines) {
            colorRGBs->value[unique_colors] = (color_rgb) { 0, 0, 0 };
        }
        byte3 size = (byte3) { chunk_voxel_length, chunk_voxel_length, chunk_voxel_length };
        nodeDepth->value = node_depth;
        fill_new_octree(chunkOctree, 0, node_depth);  // clear chunk
        if (zox_has(e, VoxRubble)) {
            byte rubble_height = 4;
            if (zox_has(e, RubbleHeight)) {
                rubble_height = zox_get_value(e, RubbleHeight)
            }
            int rubble_count = 200;
            if (zox_has(e, RubbleCount)) {
                rubble_count = zox_get_value(e, RubbleCount)
            }
            vox_rubble(chunkOctree, node_depth, size, voxel_range, rubble_count, rubble_height);
        } else if (zox_has(e, BlendVox)) {
            const color under_color = zox_get_value(e, SecondaryColor)
            for (int j = colors_count; j < colors_count + unique_colors; j++) {
                color_rgb new_color = color_to_color_rgb(under_color);
                color_rgb_multiply_float(&new_color, 0.7f + 0.6f * (rand() % 100) * 0.01f);
                add_to_ColorRGBs(colorRGBs, new_color);
            }
            const byte2 voxel_range_2 = (byte2) { colors_count + 1, colors_count + unique_colors };
            color_rgb dirt_dark_voxel = color_to_color_rgb(under_color);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colorRGBs, dirt_dark_voxel);
            byte black_voxel_3 = colorRGBs->length;
            voronoi3D(chunkOctree, node_depth, size, voxel_range_2, black_voxel_3);
            noise_vox(chunkOctree, node_depth, size, voxel_range_2, black_voxel_3);  // avoids black ones
            // create new chunk node here, blend two using mask?
            const byte grass_position = chunk_voxel_length - chunk_voxel_length / 3;
            byte3 voxel_position;
            for (voxel_position.x = 0; voxel_position.x < size.x; voxel_position.x++) {
                for (voxel_position.z = 0; voxel_position.z < size.z; voxel_position.z++) {
                    const byte grass_height = grass_position - rand() % grass_random;
                    for (voxel_position.y = grass_height; voxel_position.y < size.y; voxel_position.y++) {
                        const byte voxel = voxel_range.x + rand() % (voxel_range.y - voxel_range.x);
                        byte2 set_voxel = (byte2) { voxel, node_depth };
                        byte3 temp_position = voxel_position;
                        set_octree_voxel(chunkOctree, &temp_position, &set_voxel, 0);
                    }
                }
            }
            // add outline between blended parts
            byte2 range_blend_1 = voxel_range;
            byte2 range_blend_2 = voxel_range_2;
            range_blend_2.y++; // include black
            color_rgb new_color = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&new_color, grass_blend_dark_multiplier);
            add_to_ColorRGBs(colorRGBs, new_color);
            byte black_voxel_2 = colorRGBs->length;
            byte2 set_voxel_black_2 = (byte2) { black_voxel_2, node_depth };
            for (voxel_position.x = 0; voxel_position.x < size.x; voxel_position.x++) {
                for (voxel_position.z = 0; voxel_position.z < size.z; voxel_position.z++) {
                    for (voxel_position.y = 1; voxel_position.y < size.y - 1; voxel_position.y++) {
                        byte3 temp_position_1 = voxel_position;
                        const byte voxel = get_octree_voxel(chunkOctree, &temp_position_1, node_depth);
                        byte3 temp_position_up = byte3_up(voxel_position);
                        const byte voxel_up = get_octree_voxel(chunkOctree, &temp_position_up, node_depth);
                        if ((voxel >= range_blend_1.x && voxel <= range_blend_1.y && voxel_up >= range_blend_2.x && voxel_up <= range_blend_2.y) || (voxel >= range_blend_2.x && voxel <= range_blend_2.y && voxel_up >= range_blend_1.x && voxel_up <= range_blend_1.y)) {
                            byte3 temp_position = voxel_position;
                            set_octree_voxel(chunkOctree, &temp_position, &set_voxel_black_2, 0);
                        }
                        byte3 temp_position_down = byte3_down(voxel_position);
                        const byte voxel_down = get_octree_voxel(chunkOctree, &temp_position_down, node_depth);
                        if ((voxel >= range_blend_1.x && voxel <= range_blend_1.y && voxel_down >= range_blend_2.x && voxel_down <= range_blend_2.y) || (voxel >= range_blend_2.x && voxel <= range_blend_2.y && voxel_down >= range_blend_1.x && voxel_down <= range_blend_1.y)) {
                            byte3 temp_position = voxel_position;
                            set_octree_voxel(chunkOctree, &temp_position, &set_voxel_black_2, 0);
                        }
                        if (voxel_position.x != size.x - 1) {
                            byte3 temp_position_right = byte3_right(voxel_position);
                            const byte voxel_right = get_octree_voxel(chunkOctree, &temp_position_right, node_depth);
                            if ((voxel >= range_blend_1.x && voxel <= range_blend_1.y && voxel_right >= range_blend_2.x && voxel_right <= range_blend_2.y) || (voxel >= range_blend_2.x && voxel <= range_blend_2.y && voxel_right >= range_blend_1.x && voxel_right <= range_blend_1.y)) {
                                byte3 temp_position = voxel_position;
                                set_octree_voxel(chunkOctree, &temp_position, &set_voxel_black_2, 0);
                            }
                        }
                        if (voxel_position.x != 0) {
                            byte3 temp_position_left = byte3_left(voxel_position);
                            const byte voxel_left  = get_octree_voxel(chunkOctree, &temp_position_left, node_depth);
                            if ((voxel >= range_blend_1.x && voxel <= range_blend_1.y && voxel_left  >= range_blend_2.x && voxel_left  <= range_blend_2.y) || (voxel >= range_blend_2.x && voxel <= range_blend_2.y && voxel_left  >= range_blend_1.x && voxel_left <= range_blend_1.y)) {
                                byte3 temp_position = voxel_position;
                                set_octree_voxel(chunkOctree, &temp_position, &set_voxel_black_2, 0);
                            }
                        }
                        if (voxel_position.z != size.z - 1) {
                            byte3 temp_position_front = byte3_front(voxel_position);
                            const byte voxel_front = get_octree_voxel(chunkOctree, &temp_position_front, node_depth);
                            if ((voxel >= range_blend_1.x && voxel <= range_blend_1.y && voxel_front >= range_blend_2.x && voxel_front <= range_blend_2.y) || (voxel >= range_blend_2.x && voxel <= range_blend_2.y && voxel_front >= range_blend_1.x && voxel_front <= range_blend_1.y)) {
                                byte3 temp_position = voxel_position;
                                set_octree_voxel(chunkOctree, &temp_position, &set_voxel_black_2, 0);
                            }
                        }
                        if (voxel_position.z != 0) {
                            byte3 temp_position_back = byte3_back (voxel_position);
                            const byte voxel_back  = get_octree_voxel(chunkOctree, &temp_position_back, node_depth);
                            if ((voxel >= range_blend_1.x && voxel <= range_blend_1.y && voxel_back >= range_blend_2.x && voxel_back <= range_blend_2.y) || (voxel >= range_blend_2.x && voxel <= range_blend_2.y && voxel_back  >= range_blend_1.x && voxel_back  <= range_blend_1.y)) {
                                byte3 temp_position = voxel_position;
                                set_octree_voxel(chunkOctree, &temp_position, &set_voxel_black_2, 0);
                            }
                        }
                    }
                }
            }
        } else if (zox_has(e, VoxNoisey)) {
            color_rgb dirt_dark_voxel = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colorRGBs, dirt_dark_voxel);
            byte black_voxel_3 = colorRGBs->length;
            noise_vox(chunkOctree, node_depth, size, voxel_range, black_voxel_3);
        } else if (zox_has(e, VoxSoil)) {
            color_rgb dirt_dark_voxel = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colorRGBs, dirt_dark_voxel);
            byte black_voxel_3 = colorRGBs->length;
            voronoi3D(chunkOctree, node_depth, size, voxel_range, black_voxel_3);
            noise_vox(chunkOctree, node_depth, size, voxel_range, black_voxel_3);
        } else {
            zox_log_error("unknown vox type [%s]", zox_get_name(e))
            generateVox->value = 0;
            continue;
        }
        if (is_generate_vox_outlines) {
            vox_outlines(chunkOctree, node_depth, size, black_voxel);
        }
#ifndef zox_disable_closing_octree_nodes
        close_same_nodes(world, chunkOctree);
#endif
        generateVox->value = 0;
        if (zox_has(e, ChunkMeshDirty)) {
            zox_set(e, ChunkMeshDirty, { chunk_dirty_state_trigger })
        }
        // zox_log("+ generated vox [%s]", zox_get_name(e))
    }
} zox_declare_system(GenerateVoxSystem)
