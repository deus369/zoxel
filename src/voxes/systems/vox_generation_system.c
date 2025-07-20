void VoxGenerationSystem(ecs_iter_t *it) {
    const byte unique_colors = 8;
    const int grass_random = 6;
    // const byte node_depth = block_vox_depth;
    // const byte chunk_voxel_length = powers_of_two_byte[node_depth];
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Color)
    zox_sys_in(VoxType)
    zox_sys_out(GenerateVox)
    zox_sys_out(VoxelNode)
    zox_sys_out(NodeDepth)
    zox_sys_out(ColorRGBs)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(Color, color2)
        zox_sys_i(VoxType, voxType)
        zox_sys_o(VoxelNode, voxelNode)
        zox_sys_o(NodeDepth, nodeDepth)
        zox_sys_o(ColorRGBs, colors)
        zox_sys_o(GenerateVox, generateVox)
        if (!generateVox->value) {
            continue;
        }
        const byte node_depth = nodeDepth->value;
        // nodeDepth->value = node_depth;
        const byte colors_count = unique_colors + is_generate_vox_outlines;
        resize_memory_component(ColorRGBs, colors, color_rgb, colors_count)
        const color_rgb color_rgb_2 = color_to_color_rgb(color2->value);
        // black color
        const byte black_voxel = unique_colors + 1;
        // colors to pick from
        const byte2 voxel_range = (byte2) { 1, unique_colors - 1 };
        // generates random colors based on primary color
        for (int j = 0; j < unique_colors; j++) {
            colors->value[j] = color_rgb_2;
            color_rgb_multiply_float(&colors->value[j], 0.7f + 0.6f * (rand() % 100) * 0.01f);
        }
        if (is_generate_vox_outlines) {
            colors->value[unique_colors] = (color_rgb) { 0, 0, 0 };
        }
        // byte3 size = byte3_single(chunk_voxel_length);
        if (voxType->value == vox_type_soil) {
            // colors
            color_rgb dirt_dark_voxel = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colors, dirt_dark_voxel);
            byte black_voxel_3 = colors->length;

            build_vox_soil(voxelNode,
                node_depth,
                voxel_range,
                black_voxel_3);

        } else if (voxType->value == vox_type_blended) {

            // Colors
            zox_geter_value(e, SecondaryColor, color, under_color)
            // generates random colors based on secondary color
            for (int j = colors_count; j < colors_count + unique_colors; j++) {
                color_rgb new_color = color_to_color_rgb(under_color);
                color_rgb_multiply_float(&new_color, 0.7f + 0.6f * (rand() % 100) * 0.01f);
                add_to_ColorRGBs(colors, new_color);
            }
            const byte2 voxel_range_2 = (byte2) { colors_count + 1, colors_count + unique_colors };
            color_rgb dirt_dark_voxel = color_to_color_rgb(under_color);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colors, dirt_dark_voxel);
            byte black_voxel_3 = colors->length;
            byte2 range_blend_1 = voxel_range;
            byte2 range_blend_2 = voxel_range_2;
            range_blend_2.y++; // include black
            color_rgb new_color = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&new_color, grass_blend_dark_multiplier);
            add_to_ColorRGBs(colors, new_color);
            byte black_voxel_2 = colors->length;

            // put indexes here
            build_vox_blended(voxelNode,
                node_depth,
                black_voxel_2,
                black_voxel_3,
                voxel_range,
                voxel_range_2,
                range_blend_1,
                range_blend_2);

        } else if (voxType->value == vox_type_rubble) {

            byte rubble_height = 4;
            if (zox_has(e, RubbleHeight)) {
                rubble_height = zox_get_value(e, RubbleHeight)
            }
            int rubble_count = 200;
            if (zox_has(e, RubbleCount)) {
                rubble_count = zox_get_value(e, RubbleCount)
            }

            build_vox_rubble(voxelNode,
                node_depth,
                voxel_range,
                rubble_count,
                rubble_height);

        } else if (voxType->value == vox_type_noisey) {

            color_rgb dirt_dark_voxel = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colors, dirt_dark_voxel);
            byte black_voxel_3 = colors->length;

            build_vox_noisey(voxelNode,
                node_depth,
                voxel_range,
                black_voxel_3);

        } else {
            zox_log_error("unknown vox type [%s]", zox_get_name(e))
            generateVox->value = 0;
            continue;
        }
        if (is_generate_vox_outlines) {
            vox_outlines(voxelNode,
                node_depth,
                black_voxel);
        }
#ifndef zox_disable_closing_octree_nodes
        close_same_nodes(world, voxelNode);
#endif
        generateVox->value = 0;
        if (zox_has(e, ChunkMeshDirty)) {
            zox_set(e, ChunkMeshDirty, { chunk_dirty_state_trigger })
        }
        // zox_log("+ generated vox [%s]", zox_get_name(e))
    }
} zox_declare_system(VoxGenerationSystem)
