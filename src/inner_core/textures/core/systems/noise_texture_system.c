void NoiseTextureSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_iter_world()
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 2);
    TextureData *textures = ecs_field(it, TextureData, 3);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 4);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 5);
    for (int i = 0; i < it->count; i++) {
        GenerateTexture *generateTexture = &generateTextures[i];
        if (generateTexture->value == 0) continue;
        TextureDirty *textureDirty = &textureDirtys[i];
        // if (textureDirty->value != 0) continue;
        const TextureSize *textureSize = &textureSizes[i];
        TextureData *textureData = &textures[i];
        ecs_entity_t e = it->entities[i];
        unsigned char texture_type = zox_texture_none;
        if (texture_mode == zox_texture_mode_graybox) {
            texture_type = zox_texture_graybox;
        } else if (zox_has(e, DirtTexture)) {
            texture_type = zox_texture_dirt;
        } else if (zox_has(e, GrassTexture)) {
            texture_type = zox_texture_grass;
        } else if (zox_has(e, SandTexture)) {
            texture_type = zox_texture_sand;
        } else if (zox_has(e, StoneTexture)) {
            texture_type = zox_texture_stone;
        } else if (zox_has(e, ObsidianTexture)) {
            texture_type = zox_texture_obsidian;
        }
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_texture_noise(textureData, textureSize, texture_type, terrain_texture_outline_type);
        generateTexture->value = 0;
        textureDirty->value = 1; // actually this only gets uploaded if has GPUTextureLink!
    }
} zox_declare_system(NoiseTextureSystem)
