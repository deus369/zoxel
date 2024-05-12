void FillTextureSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_field_in(TextureSize, textureSizes, 4)
    zox_field_in(Color, colors, 6)
    zox_field_out(TextureDirty, textureDirtys, 2)
    zox_field_out(TextureData, textureDatas, 3)
    zox_field_out(GenerateTexture, generateTextures, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(GenerateTexture, generateTextures, generateTexture)
        if (!generateTexture->value) continue;
        zox_field_i_out(TextureDirty, textureDirtys, textureDirty)
        if (textureDirty->value) continue;
        zox_field_i_in(TextureSize, textureSizes, textureSize)
        zox_field_i_in(Color, colors, color2)
        zox_field_i_out(TextureData, textureDatas, textureData)
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_texture_fill(textureData, textureSize->value, color2->value);
        generateTexture->value = 0;
        textureDirty->value = 1; // actually this only gets uploaded if has GPUTextureLink!
    }
} zox_declare_system(FillTextureSystem)
