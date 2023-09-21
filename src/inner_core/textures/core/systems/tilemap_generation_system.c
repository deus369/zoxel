// uses terrain's texture links to generate a tilemap
//  todo: system before that sets texture links from voxel links
// todo: debug why array indexes go out of bounds!

// for (int j = 0; j < textureLinks->length; j++) {
// if (!ecs_is_valid(it->world, texture_entity)) zoxel_log("issue with texture at [%i]\n", j);
// if (!ecs_is_valid(it->world, texture_entity)) continue;
// if (voxel_texture_data->length == 0) zoxel_log("    ! issue with texture at [%i] - %lu\n", j, texture_entity);
// if (voxel_texture_data->length == 0) continue;
// const TextureSize *voxel_texture_size = ecs_get(it->world, texture_entity, TextureSize);
/*if (texture_index >= voxel_texture_data->length) zoxel_log("texture_index out of bounds [%i / %i]\n", texture_index, voxel_texture_data->length);
if (texture_index >= voxel_texture_data->length) textureData->value[j].r = 233;*/
// set random color for now
/*for (int j = 0; j < textureData->length; j++) {
    textureData->value[j].r = 145;
    textureData->value[j].g = 24;
    textureData->value[j].b = 133;
}*/

void TilemapGenerationSystem(ecs_iter_t *it) {
    // int2 default_texture_size = (int2) { 32, 32 }; // 16
    ecs_world_t *world = it->world;
    const TilemapSize *tilemapSizes = ecs_field(it, TilemapSize, 2);
    const TextureLinks *textureLinkss = ecs_field(it, TextureLinks, 3);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 4);
    TextureSize *textureSizes = ecs_field(it, TextureSize, 5);
    TextureData *textureDatas = ecs_field(it, TextureData, 6);
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 7);
    TilemapUVs *tilemapUVss = ecs_field(it, TilemapUVs, 8);
    for (int i = 0; i < it->count; i++) {
        GenerateTexture *generateTexture = &generateTextures[i];
        if (!generateTexture->value) continue;
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

        const TextureSize *first_texture_size = ecs_get(world, textureLinks->value[0], TextureSize);
        textureSize->value.x = tilemapSize->value.x * first_texture_size->value.x;
        textureSize->value.y = tilemapSize->value.y * first_texture_size->value.y;
        re_initialize_memory_component(textureData, color, textureSize->value.x * textureSize->value.y)
        re_initialize_memory_component(tilemapUVs, float2, textureLinks->length * 4)
        // todo: set uvs per each texture, float2 x 4 per texture
        //  get the float size by dividing 1.0f by the rows count
        //  use the tilemap_pixel_position when placing them
        //  it should atm get a minimum power of 2, in this case for 5 voxels, it would create a 4x4 tilemap
        int texture_entity_index = 0;
        int2 texture_position = int2_zero;
        for (texture_position.y = 0; texture_position.y < tilemapSize->value.y; texture_position.y++) {
            for (texture_position.x = 0; texture_position.x < tilemapSize->value.x; texture_position.x++) {
                int2 tilemap_position = (int2) { texture_position.x * first_texture_size->value.x, texture_position.y * first_texture_size->value.y };
                // call function here to place texture in tilemap
                // perhaps just list all the float2s per texture inside a float2 array called TilemapUVs
                ecs_entity_t texture_entity = textureLinks->value[texture_entity_index];
                const TextureData *voxel_texture_data = ecs_get(world, texture_entity, TextureData);
                const TextureSize *voxel_texture_size = ecs_get(world, texture_entity, TextureSize);
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
                // zoxel_log(" + placing tile [%i] at [%ix%i]\n", texture_entity_index, tilemap_position.x, tilemap_position.y);
                texture_entity_index++;
                if (texture_entity_index >= textureLinks->length) {
                    texture_position.x = tilemapSize->value.x;
                    texture_position.y = tilemapSize->value.y;
                    // zoxel_log(" ! finished placing at [%i]\n", texture_entity_index);
                }
            }
        }
        textureDirty->value = 1;
        generateTexture->value = 0;
        // zoxel_log("    > tilemap texture generated [%lu]\n", it->entities[i]);
        // generate_tilemap(it->world, textureData, tilemapSize, textures);
        // zoxel_log("    > tilemap generated [%lu] textures [%i] tilemapUVs [%i]\n", it->entities[i], textureLinks->length, tilemapUVs->length);
    }
} zox_declare_system(TilemapGenerationSystem)