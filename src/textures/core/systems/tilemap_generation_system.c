// uses terrain's texture links to generate a tilemap
// todo: support for multiple sizes, would have to place them in? or something
void TilemapGenerationSystem(ecs_iter_t *it) {
    const byte uvs_per_tile = 4;
    zox_field_world()
    zox_field_in(TilemapSize, tilemapSizes, 1)
    zox_field_in(TextureLinks, textureLinkss, 2)
    zox_field_out(GenerateTexture, generateTextures, 3)
    zox_field_out(TextureSize, textureSizes, 4)
    zox_field_out(TextureData, textureDatas, 5)
    zox_field_out(TextureDirty, textureDirtys, 6)
    zox_field_out(TilemapUVs, tilemapUVss, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateTexture, generateTextures, generateTexture)
        if (generateTexture->value != zox_generate_texture_generate) continue;
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        if (textureDirty->value) continue;
        zox_field_i(TextureLinks, textureLinkss, textureLinks)
        if (textureLinks->length == 0) {
            zox_log(" ! tilemap has no textures\n")
            continue;
        }
        zox_field_i(TilemapSize, tilemapSizes, tilemapSize)
        if (tilemapSize->value.x == 0) {
            zox_log(" ! tilemapSize->value.x is 0\n")
            continue;
        }
        zox_field_o(TextureData, textureDatas, textureData)
        zox_field_o(TextureSize, textureSizes, textureSize)
        zox_field_o(TilemapUVs, tilemapUVss, tilemapUVs)
        // generate textureSize based on TilemapSize
        const ecs_entity_t first_texture = textureLinks->value[0];
        if (!zox_valid(first_texture)) {
            zox_log(" ! first_texture is null in tilemap generation system\n")
            continue;
        }
        const int2 unit_size = zox_get_value(first_texture, TextureSize)
        const float tile_uv_size = 1.0f / ((float) tilemapSize->value.x); // for example, 1 / 8 if size is 8
        textureSize->value.x = tilemapSize->value.x * unit_size.x;
        textureSize->value.y = tilemapSize->value.y * unit_size.y;
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        int2 texture_position = int2_zero;
        int texture_index = 0;
        for (int j = 0; j < textureData->length; j++) textureData->value[j] = color_white;
        for (texture_position.y = 0; texture_position.y < tilemapSize->value.y; texture_position.y++) {
            for (texture_position.x = 0; texture_position.x < tilemapSize->value.x; texture_position.x++) {
                if (texture_index >= textureLinks->length) {
                    break;
                    break;
                }
                const ecs_entity_t texture_entity = textureLinks->value[texture_index];
                if (!zox_valid(texture_entity) || !zox_has(texture_entity, TextureData)) {
                    zox_log(" ! [tilemap generation system] texture null [%lu] - index [%i]\n", texture_entity, texture_index)
                    texture_index++;
                    continue;
                }
                const TextureData *voxel_texture_data = zox_get(texture_entity, TextureData)
                if (!voxel_texture_data->value) {
                    zox_log(" ! voxel_texture_data->value is null\n")
                    texture_index++;
                    continue;
                }
                const int2 texture_size = zox_get_value(texture_entity, TextureSize)
                const int2 tilemap_position = (int2) { texture_position.x * unit_size.x, texture_position.y * unit_size.y };
                // call function here to place texture in tilemap
                // perhaps just list all the float2s per texture inside a float2 array called TilemapUVs
                // tod: refactor - make this into a function
                int2 pixel_position = int2_zero;
                for (pixel_position.x = 0; pixel_position.x < texture_size.x; pixel_position.x++) {
                    for (pixel_position.y = 0; pixel_position.y < texture_size.y; pixel_position.y++) {
                        int2 tilemap_pixel_position = int2_add(pixel_position, tilemap_position);
                        int tilemap_index = int2_array_index(tilemap_pixel_position, textureSize->value);
                        if (tilemap_index >= textureData->length) {
                            zox_log(" ! tilemap_index >= textureData->length\n")
                            continue;
                        }
                        int texture_index = int2_array_index(pixel_position, texture_size);
                        if (texture_index >= voxel_texture_data->length) {
                            // zox_log(" ! texture_index >= voxel_texture_data->length\n")
                            continue;
                        }
                        textureData->value[tilemap_index] = voxel_texture_data->value[texture_index];
                    }
                }
                // zox_log(" + placed [%i] texture in tilemap s [%ix%i] p [%ix%i]\n", texture_index, texture_size.x, texture_size.y, tilemap_position.x, tilemap_position.y)
                texture_index++;
            }
        }
        texture_index = 0;
        resize_memory_component(TilemapUVs, tilemapUVs, float2, textureLinks->length * uvs_per_tile)
        for (texture_position.y = 0; texture_position.y < tilemapSize->value.y; texture_position.y++) {
            for (texture_position.x = 0; texture_position.x < tilemapSize->value.x; texture_position.x++) {
                if (texture_index >= textureLinks->length) {
                    break;
                    break;
                }
                const int2 tilemap_position = (int2) { texture_position.x * unit_size.x, texture_position.y * unit_size.y };
                const float2 tile_uv = (float2) { tilemap_position.x / (float) textureSize->value.x, tilemap_position.y / (float) textureSize->value.y };
                tilemapUVs->value[texture_index * 4 + 3] = (float2) { tile_uv.x, tile_uv.y + tile_uv_size };
                tilemapUVs->value[texture_index * 4 + 2] = (float2) { tile_uv.x + tile_uv_size, tile_uv.y + tile_uv_size };
                tilemapUVs->value[texture_index * 4 + 1] = (float2) { tile_uv.x + tile_uv_size, tile_uv.y };
                tilemapUVs->value[texture_index * 4 + 0] = (float2) { tile_uv.x, tile_uv.y };
                texture_index++;
                if (texture_index >= textureLinks->length) {
                    break;
                    break;
                }
            }
        }
        // generateTexture->value = 0;
        textureDirty->value = 1;
        // zox_log(" > tilemap generated: size [%ix%i] unit size [%ix%i]\n", textureSize->value.x, textureSize->value.y, unit_size.x, unit_size.y)
    }
} zox_declare_system(TilemapGenerationSystem)


        /*byte is_generating = 0;
        for (int j = 0; j < textureLinks->length; j++) {
            const ecs_entity_t texture = textureLinks->value[j];
            if (zox_gett_value(texture, GenerateTexture)) {
                is_generating = 1;
                break;
            }
        }
        if (is_generating) {
            zox_log(" > tilemap texture data still generating\n")
            continue;
        }*/
                /*tilemapUVs->value[texture_entity_index * 4 + 0] = (float2) { tile_uv.x, tile_uv.y };
                tilemapUVs->value[texture_entity_index * 4 + 1] = (float2) { tile_uv.x, tile_uv.y + tile_uv_size };
                tilemapUVs->value[texture_entity_index * 4 + 2] = (float2) { tile_uv.x + tile_uv_size, tile_uv.y + tile_uv_size };
                tilemapUVs->value[texture_entity_index * 4 + 3] = (float2) { tile_uv.x + tile_uv_size, tile_uv.y };*/

                // set voxel uvs here
                /*float2 tile_uv = (float2) { tilemap_position.x / (float) textureSize->value.x, tilemap_position.y / (float) textureSize->value.y };
                tilemapUVs->value[texture_index * 4 + 3] = (float2) { tile_uv.x, tile_uv.y + tile_uv_size };
                tilemapUVs->value[texture_index * 4 + 2] = (float2) { tile_uv.x + tile_uv_size, tile_uv.y + tile_uv_size };
                tilemapUVs->value[texture_index * 4 + 1] = (float2) { tile_uv.x + tile_uv_size, tile_uv.y };
                tilemapUVs->value[texture_index * 4 + 0] = (float2) { tile_uv.x, tile_uv.y };
                zox_log(" + placed [%i] texture in tilemap s [%ix%i] p [%ix%i]\n", texture_index, texture_size.x, texture_size.y, tilemap_position.x, tilemap_position.y)*/
