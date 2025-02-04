// using an axis and VoxLink, generates a texture by grabbing the first voxel on a given side
void generate_vox_texture(color *data, const int2 size, const ChunkOctree *chunk, const color_rgb *colors, unsigned char side) {
    if  (chunk == NULL) return;
    const color air_vox_color = (color) { 15, 15, 15, 255 };
    int index = 0;
    int x = 0;
    if (side == block_side_left || side == block_side_right) {
        if (side == block_side_right) x = size.y - 1;
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                byte3 node_position = (byte3) { x, i, j };
                unsigned char voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                unsigned char is_darken = 0;
                if (voxel == 0) {
                    is_darken = 1;
                    if (side == block_side_left) {
                        for (int k = 0; k < size.y; k++) {
                            node_position = (byte3) { k, i, j };
                            voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                            if (voxel) break;
                        }
                    } else {
                        for (int k = size.y - 1; k >= 0; k--) {
                            node_position = (byte3) { k, i, j };
                            voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                            if (voxel) break;
                        }
                    }
                }
                if (voxel == 0) data[index] = air_vox_color;
                else data[index] = color_rgb_to_color(colors[voxel - 1]);
                if (is_darken) color_multiply_float(&data[index], 0.8f);
                index++;
            }
        }
    } else if (side == block_side_down || side == block_side_up) {
        if (side == block_side_up) x = size.y - 1;
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                byte3 node_position = (byte3) { i, x, j };
                unsigned char voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                unsigned char is_darken = 0;
                if (voxel == 0) {
                    is_darken = 1;
                    if (side == block_side_down) {
                        for (int k = 0; k < size.y; k++) {
                            node_position = (byte3) { i, k, j };
                            voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                            if (voxel) break;
                        }
                    } else {
                        for (int k = size.y - 1; k >= 0; k--) {
                            node_position = (byte3) { i, k, j };
                            voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                            if (voxel) break;
                        }
                    }
                }
                if (voxel == 0) data[index] = air_vox_color;
                else data[index] = color_rgb_to_color(colors[voxel - 1]);
                if (is_darken) color_multiply_float(&data[index], 0.8f);
                index++;
            }
        }
    } else if (side == block_side_back || side ==  block_side_front) {
        if (side == block_side_front) x = size.y - 1;
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                byte3 node_position = (byte3) { i, j, x };
                unsigned char voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                unsigned char is_darken = 0;
                if (voxel == 0) {
                    is_darken = 1;
                    if (side == block_side_back) {
                        for (int k = 0; k < size.y; k++) {
                            node_position = (byte3) { i, j, k };
                            voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                            if (voxel) break;
                        }
                    } else {
                        for (int k = size.y - 1; k >= 0; k--) {
                            node_position = (byte3) { i, j, k };
                            voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                            if (voxel) break;
                        }
                    }
                }
                if (voxel == 0) data[index] = air_vox_color;
                else data[index] = color_rgb_to_color(colors[voxel - 1]);
                if (is_darken) color_multiply_float(&data[index], 0.8f);
                index++;
            }
        }

    }
}

void VoxTextureSystem(ecs_iter_t *it) {
    zox_field_in(TextureSize, textureSizes, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_in(VoxBakeSide, voxBakeSides, 3)
    zox_field_out(GenerateTexture, generateTextures, 4)
    zox_field_out(TextureData, textureDatas, 5)
    zox_field_out(TextureDirty, textureDirtys, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateTexture, generateTextures, generateTexture)
        if (generateTexture->value != zox_generate_texture_generate) continue;
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value || zox_gett_value(voxLink->value, GenerateVox)) continue;
        const ColorRGBs *colorRGBs = zox_get(voxLink->value, ColorRGBs)
        const ChunkOctree *chunk = zox_get(voxLink->value, ChunkOctree)
        zox_field_i(TextureSize, textureSizes, textureSize)
        zox_field_i(VoxBakeSide, voxBakeSides, voxBakeSide)
        zox_field_o(TextureData, textureDatas, textureData)
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_vox_texture(textureData->value, textureSize->value, chunk, colorRGBs->value, voxBakeSide->value);
        // generateTexture->value = 0;
        textureDirty->value = 1; // actually not using this for tilemap!
        // for (int j = 0; j < textureData->length; j++) textureData->value[j] = color_red;
    }
} zox_declare_system(VoxTextureSystem)
