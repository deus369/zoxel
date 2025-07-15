// uses terrain's texture links to generate a tilemap
// todo: support for multiple sizes, would have to place them in? or something
void TilemapGenerationSystem(ecs_iter_t *it) {
    const byte uvs_per_tile = 4;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TilemapSize)
    zox_sys_in(TextureLinks)
    zox_sys_out(GenerateTexture)
    zox_sys_out(TextureSize)
    zox_sys_out(TextureData)
    zox_sys_out(TextureDirty)
    zox_sys_out(TilemapUVs)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TilemapSize, tilemapSize)
        zox_sys_i(TextureLinks, textureLinks)
        zox_sys_o(GenerateTexture, generateTexture)
        zox_sys_o(TextureSize, textureSize)
        zox_sys_o(TextureData, textureData)
        zox_sys_o(TextureDirty, textureDirty)
        zox_sys_o(TilemapUVs, tilemapUVs)
        if (generateTexture->value != zox_generate_texture_generate || textureDirty->value) {
            continue;
        }
        if (!textureLinks->length || !tilemapSize->value.x) {
            zox_log_error("issue with tilemap data!")
            continue;
        }
        // generate textureSize based on TilemapSize
        const ecs_entity_t first_texture = textureLinks->value[0];
        if (!zox_valid(first_texture)) {
            zox_log_error("first_texture is null in tilemap generation system\n")
            continue;
        }
        const int2 unit_size = zox_get_value(first_texture, TextureSize)
        const float tile_uv_size = 1.0f / ((float) tilemapSize->value.x); // for example, 1 / 8 if size is 8
        textureSize->value.x = tilemapSize->value.x * unit_size.x;
        textureSize->value.y = tilemapSize->value.y * unit_size.y;
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        int2 texture_position = int2_zero;
        int texture_index = 0;
        for (int j = 0; j < textureData->length; j++) {
            textureData->value[j] = color_white;
        }
        for (texture_position.y = 0; texture_position.y < tilemapSize->value.y && texture_index < textureLinks->length; texture_position.y++) {
            for (texture_position.x = 0; texture_position.x < tilemapSize->value.x && texture_index < textureLinks->length; texture_position.x++) {
                const ecs_entity_t texture_entity = textureLinks->value[texture_index];
                if (!zox_valid(texture_entity) || !zox_has(texture_entity, TextureData)) {
                    zox_log_error("invalid texture [%lu] index [%i]", texture_entity, texture_index)
                    texture_index++;
                    continue;
                }
                zox_geter(texture_entity, TextureData, voxel_texture_data)
                if (!voxel_texture_data->value) {
                    zox_log_error("invalid texture data [%lu] index [%i]", texture_entity, texture_index)
                    texture_index++;
                    continue;
                }
                const int2 texture_size = zox_get_value(texture_entity, TextureSize)
                const int2 tilemap_position = (int2) { texture_position.x * unit_size.x, texture_position.y * unit_size.y };

                // tod: refactor - make this into a function
                int2 pixel_position = int2_zero;
                for (pixel_position.x = 0; pixel_position.x < texture_size.x; pixel_position.x++) {
                    for (pixel_position.y = 0; pixel_position.y < texture_size.y; pixel_position.y++) {
                        int2 tilemap_pixel_position = int2_add(pixel_position, tilemap_position);
                        int tilemap_index = int2_array_index(tilemap_pixel_position, textureSize->value);
                        if (tilemap_index >= textureData->length) {
                            zox_log_error("tilemap_index [%i] >= textureData->length [%i]", tilemap_index, textureData->length)
                            textureDirty->value = 1;
                            return;
                        }
                        int texture_index = int2_array_index(pixel_position, texture_size);
                        if (texture_index >= voxel_texture_data->length) {
                            continue;
                        }
                        textureData->value[tilemap_index] = voxel_texture_data->value[texture_index];
                    }
                }
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
                // 4 uvs per face
                tilemapUVs->value[texture_index * 4 + 3] = (float2) {
                    tile_uv.x, tile_uv.y + tile_uv_size };
                tilemapUVs->value[texture_index * 4 + 2] = (float2) {
                    tile_uv.x + tile_uv_size, tile_uv.y + tile_uv_size };
                tilemapUVs->value[texture_index * 4 + 1] = (float2) {
                    tile_uv.x + tile_uv_size, tile_uv.y };
                tilemapUVs->value[texture_index * 4 + 0] = (float2) {
                    tile_uv.x, tile_uv.y };
                texture_index++;
                if (texture_index >= textureLinks->length) {
                    break;
                    break;
                }
            }
        }
        textureDirty->value = 1;
    }
} zox_declare_system(TilemapGenerationSystem)