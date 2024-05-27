// using an axis and VoxLink, generates a texture by grabbing the first voxel on a given side
// todo: fix flower positioning
void generate_vox_texture(color *data, const int2 size, const ChunkOctree *chunk, const color_rgb *colors, unsigned char side) {
    // for now just get top axis
    int index = 0;
    if (side == block_side_left || side == block_side_right) {
        // zox_log(" generate_vox_texture x side %i\n", side)
        int x = 0;
        if (side == block_side_right) x = size.y - 1;
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                byte3 node_position = (byte3) { x, i, j };
                const unsigned voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                if (voxel == 0) data[index] = (color) { 0, 0, 0, 0 };
                else data[index] = color_rgb_to_color(colors[voxel - 1]);
                //if (side == block_side_right) data[index] = (color) { 255, 0, 0, 255 };
                //else data[index] = (color) { 0, 255, 0, 255 };
                index++;
            }
        }
    } else if (side == block_side_down || side == block_side_up) {
        // zox_log(" generate_vox_texture y side %i\n", side)
        int x = 0;
        if (side == block_side_up) x = size.y - 1;
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                byte3 node_position = (byte3) { i, x, j };
                // const unsigned voxel = 1; // get_first_voxel_from_z(chunk, max_octree_depth, 0);
                const unsigned voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                if (voxel == 0) data[index] = (color) { 0, 0, 0, 0 };
                else data[index] = color_rgb_to_color(colors[voxel - 1]);
                index++;
            }
        }
    } else if (side == block_side_back || side ==  block_side_front) {
        // zox_log(" generate_vox_texture z side %i\n", side)
        int x = 0;
        if (side == block_side_front) x = size.y - 1;
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                byte3 node_position = (byte3) { i, j, x };
                const unsigned voxel = get_octree_voxel(chunk, &node_position, max_octree_depth);
                if (voxel == 0) data[index] = (color) { 0, 0, 0, 0 };
                else data[index] = color_rgb_to_color(colors[voxel - 1]);
                // data[index] = (color) { 0, 0, 255, 255 };
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
        if (!generateTexture->value) continue;
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        const unsigned char generate_vox = zox_get_value(voxLink->value, GenerateVox)
        if (generate_vox) continue;
        const ColorRGBs *colorRGBs = zox_get(voxLink->value, ColorRGBs)
        const ChunkOctree *chunk = zox_get(voxLink->value, ChunkOctree)
        zox_field_i(TextureSize, textureSizes, textureSize)
        zox_field_i(VoxBakeSide, voxBakeSides, voxBakeSide)
        zox_field_o(TextureData, textureDatas, textureData)
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_vox_texture(textureData->value, textureSize->value, chunk, colorRGBs->value, voxBakeSide->value);
        generateTexture->value = 0;
        textureDirty->value = 1;
        /*zox_log(" +  VoxTextureSystem::\n")
        zox_log("   +  c1: - %xx%xx%x\n", colorRGBs->value[0].r, colorRGBs->value[0].g, colorRGBs->value[0].b)
        zox_log("   +  c2: - %xx%xx%x\n", colorRGBs->value[1].r, colorRGBs->value[1].g, colorRGBs->value[1].b)*/
    }
} zox_declare_system(VoxTextureSystem)
