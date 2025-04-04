void FillTextureSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_field_in(TextureSize, textureSizes, 4)
    zox_field_in(Color, colors, 6)
    zox_field_out(TextureDirty, textureDirtys, 2)
    zox_field_out(TextureData, textureDatas, 3)
    zox_field_out(GenerateTexture, generateTextures, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateTexture, generateTextures, generateTexture)
        if (generateTexture->value != zox_generate_texture_generate) {
            continue;
        }
        zox_field_i(TextureSize, textureSizes, textureSize)
        zox_field_i(Color, colors, fill_color)
        zox_field_o(TextureData, textureDatas, textureData)
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_texture_fill(textureData->value, textureSize->value, fill_color->value);
        textureDirty->value = 1; // actually this only gets uploaded if has GPUTextureLink!
    }
} zox_declare_system(FillTextureSystem)
