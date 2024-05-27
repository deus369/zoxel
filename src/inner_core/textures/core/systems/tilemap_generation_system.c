// uses terrain's texture links to generate a tilemap
void TilemapGenerationSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(TilemapSize, tilemapSizes, 2)
    zox_field_in(TextureLinks, textureLinkss, 3)
    zox_field_out(GenerateTexture, generateTextures, 4)
    zox_field_out(TextureSize, textureSizes, 5)
    zox_field_out(TextureData, textureDatas, 6)
    zox_field_out(TextureDirty, textureDirtys, 7)
    zox_field_out(TilemapUVs, tilemapUVss, 8)
    for (int i = 0; i < it->count; i++) {
        GenerateTexture *generateTexture = &generateTextures[i];
        if (generateTexture->value != 2) continue;
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value) continue;
        const TextureLinks *textureLinks = &textureLinkss[i];
        if (textureLinks->length == 0) {
            textureDirty->value = 1;
            continue;
        }
        const TilemapSize *tilemapSize = &tilemapSizes[i];
        TextureData *textureData = &textureDatas[i];
        TextureSize *textureSize = &textureSizes[i];
        TilemapUVs *tilemapUVs = &tilemapUVss[i];
        float tile_size = 1.0f / ((float) tilemapSize->value.x);
        // generate textureSize based on TilemapSize
        ecs_entity_t first_texture = textureLinks->value[0];
        const TextureSize *first_texture_size = zox_get(first_texture, TextureSize)
        // todo: support for multiple sizes, would have to place them in? or something
        textureSize->value.x = tilemapSize->value.x * first_texture_size->value.x;
        textureSize->value.y = tilemapSize->value.y * first_texture_size->value.y;
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        const unsigned char uvs_per_tile = 4;
        resize_memory_component(TilemapUVs, tilemapUVs, float2, textureLinks->length * uvs_per_tile)
        int texture_entity_index = 0;
        int2 texture_position = int2_zero;
        for (texture_position.y = 0; texture_position.y < tilemapSize->value.y; texture_position.y++) {
            for (texture_position.x = 0; texture_position.x < tilemapSize->value.x; texture_position.x++) {
                int2 tilemap_position = (int2) { texture_position.x * first_texture_size->value.x, texture_position.y * first_texture_size->value.y };
                // call function here to place texture in tilemap
                // perhaps just list all the float2s per texture inside a float2 array called TilemapUVs
                const ecs_entity_t texture_entity = textureLinks->value[texture_entity_index];
                const TextureData *voxel_texture_data = zox_get(texture_entity, TextureData)
                const TextureSize *voxel_texture_size = zox_get(texture_entity, TextureSize)
                // tod: refactor - make this into a function
                int2 pixel_position = int2_zero;
                for (pixel_position.x = 0; pixel_position.x < voxel_texture_size->value.x; pixel_position.x++) {
                    for (pixel_position.y = 0; pixel_position.y < voxel_texture_size->value.y; pixel_position.y++) {
                        int2 tilemap_pixel_position = int2_add(pixel_position, tilemap_position);
                        int tilemap_index = int2_array_index(tilemap_pixel_position, textureSize->value);
                        if (tilemap_index >= textureData->length) continue;
                        int texture_index = int2_array_index(pixel_position, voxel_texture_size->value);
                        if (texture_index >= voxel_texture_data->length) continue;
                        textureData->value[tilemap_index] = voxel_texture_data->value[texture_index];
                    }
                }
                // add uvs here
                float2 tile_uv = (float2) { tilemap_position.x / (float) textureSize->value.x, tilemap_position.y / (float) textureSize->value.y };
                tilemapUVs->value[texture_entity_index * 4 + 0] = (float2) { tile_uv.x, tile_uv.y };
                tilemapUVs->value[texture_entity_index * 4 + 1] = (float2) { tile_uv.x, tile_uv.y + tile_size };
                tilemapUVs->value[texture_entity_index * 4 + 2] = (float2) { tile_uv.x + tile_size, tile_uv.y + tile_size };
                tilemapUVs->value[texture_entity_index * 4 + 3] = (float2) { tile_uv.x + tile_size, tile_uv.y };
                texture_entity_index++;
                if (texture_entity_index >= textureLinks->length) {
                    texture_position.x = tilemapSize->value.x;
                    texture_position.y = tilemapSize->value.y;
                }
            }
        }
        textureDirty->value = 1;
        generateTexture->value = 0;
    }
} zox_declare_system(TilemapGenerationSystem)
