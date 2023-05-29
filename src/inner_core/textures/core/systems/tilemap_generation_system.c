// uses terrain's texture links to generate a tilemap
//  todo: system before that sets texture links from voxel links
void generate_tilemap(ecs_world_t *world, TextureData *textureData, const TilemapSize *tilemapSize) {

}

void TilemapGenerationSystem(ecs_iter_t *it) {
    const TilemapSize *tilemapSizes = ecs_field(it, TilemapSize, 2);
    const TextureLinks *textureLinkss = ecs_field(it, TextureLinks, 3);
    const GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 4);
    TextureSize *textureSizes = ecs_field(it, TextureSize, 5);
    TextureData *textureDatas = ecs_field(it, TextureData, 6);
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 7);
    for (int i = 0; i < it->count; i++) {
        const GenerateTexture *generateTexture = &generateTextures[i];
        if (generateTexture->value == 0) continue;
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value != 0) continue;
        const TextureLinks *textureLinks = &textureLinkss[i];
        const TilemapSize *tilemapSize = &tilemapSizes[i];
        TextureData *textureData = &textureDatas[i];
        TextureSize *textureSize = &textureSizes[i];
        // generate textureSize based on TilemapSize
        textureSize->value.x = tilemapSize->value.x * 16;
        textureSize->value.y = tilemapSize->value.y * 16;
        re_initialize_memory_component(textureData, color, textureSize->value.x * textureSize->value.y);
        // generate_tilemap(it->world, textureData, tilemapSize, textures);
        textureDirty->value = 1;
        // if (is_dirt) zoxel_log("    > tilemap generated [%lu]\n", it->entities[i]);
    }
}
zox_declare_system(TilemapGenerationSystem)