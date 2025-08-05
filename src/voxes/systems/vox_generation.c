define_fun_stopwatch(time_vox_generation, 0);

// todo: generate colors in another system
// todo: split processes up to nodes
// todo: add unique colors as a property too
void VoxGenerationSystem(ecs_iter_t *it) {
    zox_ts_begin(vox_generation);
    const byte unique_colors = 16;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(GenerateVox)
    zox_sys_in(Color)
    zox_sys_in(VoxType)
    zox_sys_out(VoxelNode)
    zox_sys_out(VoxelNodeDirty)
    zox_sys_out(NodeDepth)
    zox_sys_out(ColorRGBs)
    byte any_dirty = 0;
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(GenerateVox, generateVox);
        if (generateVox->value == zox_dirty_active) {
            any_dirty = 1;
            break;
        }
    }
    if (!any_dirty) {
        zox_ts_end(vox_generation, 3, zox_profile_system_vox_generation);
        return;
    }
    startwatch(time_vox_generation);
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(Color, color2)
        zox_sys_i(VoxType, voxType)
        zox_sys_i(GenerateVox, generateVox)
        zox_sys_o(VoxelNode, node)
        zox_sys_o(VoxelNodeDirty, nodeDirty)
        zox_sys_o(NodeDepth, nodeDepth)
        zox_sys_o(ColorRGBs, colors)
        if (generateVox->value != zox_dirty_active) {
            continue;
        }
        const byte node_depth = nodeDepth->value;
        // nodeDepth->value = node_depth;
        const byte colors_count = unique_colors + is_generate_vox_outlines;
        initialize_ColorRGBs(colors, colors_count);

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

        byte vregions = 16;
        if (zox_has(e, VRegions)) {
            vregions = zox_get_value(e, VRegions);
        }


        write_lock_VoxelNode(node);
        // byte3 size = byte3_single(chunk_voxel_length);
        if (voxType->value == vox_type_soil) {
            // colors
            color_rgb dirt_dark_voxel = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colors, dirt_dark_voxel);
            byte black_voxel_3 = colors->length;

            build_vox_soil(node,
                node_depth,
                voxel_range,
                black_voxel_3,
                vregions);

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
            build_vox_blended(node,
                node_depth,
                black_voxel_2,
                black_voxel_3,
                voxel_range,
                voxel_range_2,
                range_blend_1,
                range_blend_2,
                vregions);

        } else if (voxType->value == vox_type_rubble) {

            byte rubble_height = 4;
            if (zox_has(e, RubbleHeight)) {
                rubble_height = zox_get_value(e, RubbleHeight)
            }
            int rubble_count = 200;
            if (zox_has(e, RubbleCount)) {
                rubble_count = zox_get_value(e, RubbleCount)
            }

            build_vox_rubble(node,
                node_depth,
                voxel_range,
                rubble_count,
                rubble_height);

        } else if (voxType->value == vox_type_noisey) {

            color_rgb dirt_dark_voxel = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colors, dirt_dark_voxel);
            byte black_voxel_3 = colors->length;

            vnoise3(node,
                node_depth,
                voxel_range,
                black_voxel_3);

        } else if (voxType->value == vox_type_bricks) {
            color_rgb dirt_dark_voxel = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colors, dirt_dark_voxel);
            byte black_voxel_3 = colors->length;

            build_vox_bricks(node,
                             node_depth,
                             voxel_range,
                             black_voxel_3);

        } else if (voxType->value == vox_type_flowers) {
            color_rgb dirt_dark_voxel = color_to_color_rgb(color2->value);
            color_rgb_multiply_float(&dirt_dark_voxel, fracture_dark_multiplier);
            add_to_ColorRGBs(colors, dirt_dark_voxel);
            byte black_voxel_3 = colors->length;
            build_vox_flower_patch(
                node,
                node_depth,
                (byte2) { voxel_range.x, voxel_range.y / 2 }, // (byte2) { 2, 6 },
                (byte2) { voxel_range.y / 2, voxel_range.y }, // (byte2) { 1, 4 },
                black_voxel_3);

        } else {
            zox_log_error("unknown vox type [%s]", zox_get_name(e));
            write_unlock_VoxelNode(node);
            continue;
        }
        if (is_generate_vox_outlines) {
            vox_outlines(node,
                node_depth,
                black_voxel);
        }
        write_unlock_VoxelNode(node);
        nodeDirty->value = zox_dirty_trigger;
        zox_log_error("Generated Vox [%s]", zox_get_name(e));
        tapwatch(time_vox_generation, "generate vox");
    }

    endwatch(time_vox_generation, "ending");
    zox_ts_end(vox_generation, 3, zox_profile_system_vox_generation);
} zox_declare_system(VoxGenerationSystem)
