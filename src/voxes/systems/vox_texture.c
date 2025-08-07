// using an axis and VoxLink, generates a texture by grabbing the first voxel on a given side
byte is_debug_sides = block_side_none; // block_side_none | block_side_front
const color air_vox_color = (color) { 15, 15, 25, 88 };

void generate_vox_debug_texture(color *data, const int2 size, byte side) {
    if (is_debug_sides == block_side_none) {
        return;
    }
    color fill = air_vox_color;
    if (is_debug_sides == block_side_up && side == block_side_up) {
        fill = (color) { 255, 0, 0, 255 };
    } else if (is_debug_sides == block_side_down && side == block_side_down) {
        fill = (color) { 55, 0, 0, 255 };
    } else if (is_debug_sides == block_side_back && side == block_side_back) {
        fill = (color) { 0, 55, 0, 255 };
    } else if (is_debug_sides == block_side_front && side == block_side_front) {
        fill = (color) { 0, 255, 0, 255 };
    } else if (is_debug_sides == block_side_left && side == block_side_left) {
        fill = (color) { 0, 0, 255, 255 };
    } else if (is_debug_sides == block_side_right && side == block_side_right) {
        fill = (color) { 0, 0, 55, 255 };
    } else {
        return;
    }
    for (int i = 0; i < size.x * size.y; i++) {
        data[i] = fill;
    }
}

void generate_vox_texture(
    color *data,
    const int2 size,
    const VoxelNode *chunk,
    const color_rgb *colors,
    byte side,
    const byte max_depth
) {
    if (chunk == NULL) {
        return;
    }
    int index = 0;
    int x = 0;
    if (side == block_side_left || side == block_side_right) {
        if (side == block_side_right) {
            x = size.y - 1;
        }
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                byte3 node_position = (byte3) { x, i, j };
                byte voxel = get_sub_node_voxel(chunk, &node_position, max_depth);
                byte is_darken = 0;
                if (voxel == 0) {
                    is_darken = 1;
                    if (side == block_side_left) {
                        for (int k = 0; k < size.y; k++) {
                            node_position = (byte3) { k, i, j };
                            voxel = get_sub_node_voxel(chunk, &node_position, max_depth);
                            if (voxel) {
                                break;
                            }
                        }
                    } else {
                        for (int k = size.y - 1; k >= 0; k--) {
                            node_position = (byte3) { k, i, j };
                            voxel = get_sub_node_voxel(chunk, &node_position, max_depth);
                            if (voxel) {
                                break;
                            }
                        }
                    }
                }
                if (voxel == 0) {
                    data[index] = air_vox_color;
                } else {
                    data[index] = color_rgb_to_color(colors[voxel - 1]);
                }
                if (is_darken) {
                    color_multiply_float(&data[index], 0.8f);
                }
                index++;
            }
        }
    } else if (side == block_side_down || side == block_side_up) {
        if (side == block_side_up) {
            x = size.y - 1;
        }
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                byte3 node_position = (byte3) { i, x, j };
                byte voxel = get_sub_node_voxel(chunk, &node_position, max_depth);
                byte is_darken = 0;
                if (voxel == 0) {
                    is_darken = 1;
                    if (side == block_side_down) {
                        for (int k = 0; k < size.y; k++) {
                            node_position = (byte3) { i, k, j };
                            voxel = get_sub_node_voxel(chunk, &node_position, max_depth);
                            if (voxel) {
                                break;
                            }
                        }
                    } else {
                        for (int k = size.y - 1; k >= 0; k--) {
                            node_position = (byte3) { i, k, j };
                            voxel = get_sub_node_voxel(chunk, &node_position, max_depth);
                            if (voxel) {
                                break;
                            }
                        }
                    }
                }
                if (voxel == 0) {
                    data[index] = air_vox_color;
                } else {
                    data[index] = color_rgb_to_color(colors[voxel - 1]);
                }
                if (is_darken) {
                    color_multiply_float(&data[index], 0.8f);
                }
                index++;
            }
        }
    } else if (side == block_side_back || side == block_side_front) {
        if (side == block_side_front) {
            x = size.y - 1;
        }
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                byte3 node_position = (byte3) { i, j, x };
                byte voxel = get_sub_node_voxel(chunk, &node_position, max_depth);
                byte is_darken = 0;
                if (voxel == 0) {
                    is_darken = 1;
                    if (side == block_side_back) {
                        for (int k = 0; k < size.y; k++) {
                            node_position = (byte3) { i, j, k };
                            voxel = get_sub_node_voxel(chunk, &node_position, max_depth);
                            if (voxel) break;
                        }
                    } else {
                        for (int k = size.y - 1; k >= 0; k--) {
                            node_position = (byte3) { i, j, k };
                            voxel = get_sub_node_voxel(chunk, &node_position, max_depth);
                            if (voxel) {
                                break;
                            }
                        }
                    }
                }
                if (voxel == 0) {
                    data[index] = air_vox_color;
                } else {
                    data[index] = color_rgb_to_color(colors[voxel - 1]);
                }
                if (is_darken) {
                    color_multiply_float(&data[index], 0.8f);
                }
                index++;
            }
        }

    }
}

void VoxTextureSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TextureSize)
    zox_sys_in(VoxLink)
    zox_sys_in(VoxBakeSide)
    zox_sys_out(GenerateTexture)
    zox_sys_out(TextureData)
    zox_sys_out(TextureDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(TextureSize, textureSize)
        zox_sys_i(VoxBakeSide, voxBakeSide)
        zox_sys_o(GenerateTexture, generateTexture)
        zox_sys_o(TextureData, textureData)
        zox_sys_o(TextureDirty, textureDirty)
        if (generateTexture->value != zox_generate_texture_generate ||
            !zox_valid(voxLink->value) ||
            !zox_has(voxLink->value, VoxelNode) ||
            (zox_has(voxLink->value, GenerateVox) && zox_gett_value(voxLink->value, GenerateVox))) {
            continue;
        }
        zox_geter(voxLink->value, ColorRGBs, colors);
        zox_geter(voxLink->value, VoxelNode, node);
        zox_geter_value(voxLink->value, NodeDepth, byte, node_depth);

        const int2 texture_size = textureSize->value;
        initialize_TextureData(textureData, texture_size.x * texture_size.y);

        read_lock_VoxelNode(node);
        generate_vox_texture(
            textureData->value,
            texture_size,
            node,
            colors->value,
            voxBakeSide->value,
            node_depth);
        generate_vox_debug_texture(
            textureData->value,
            texture_size,
            voxBakeSide->value);
        read_unlock_VoxelNode(node);

        textureDirty->value = 1; // actually not using this for tilemap!
    }
} zox_declare_system(VoxTextureSystem)