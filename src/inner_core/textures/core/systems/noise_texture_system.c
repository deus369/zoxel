void NoiseTextureSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_iter_world()
    zox_field_in(TextureSize, textureSizes, 1)
    zox_field_in(Color, colors, 5)
    zox_field_out(GenerateTexture, generateTextures, 2)
    zox_field_out(TextureDirty, textureDirtys, 3)
    zox_field_out(TextureData, textureDatas, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(GenerateTexture, generateTextures, generateTexture)
        if (generateTexture->value == 0) continue;
        zox_field_e()
        zox_field_i_in(TextureSize, textureSizes, textureSize)
        zox_field_i_in(Color, colors, fill_color)
        zox_field_i_out(TextureDirty, textureDirtys, textureDirty)
        zox_field_i_out(TextureData, textureDatas, textureData)
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
        generate_texture_noise(textureData->value, textureSize->value, texture_type, terrain_texture_outline_type, fill_color->value);
        generateTexture->value = 0;
        textureDirty->value = 1; // remember: this only gets uploaded if has GPUTextureLink!
    }
} zox_declare_system(NoiseTextureSystem)
