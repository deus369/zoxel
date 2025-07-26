void FillTextureSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_sys_begin()
    zox_sys_in(TextureSize)
    zox_sys_in(Color)
    zox_sys_out(TextureData)
    zox_sys_out(GenerateTexture)
    zox_sys_out(TextureDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TextureSize, textureSize)
        zox_sys_i(Color, fill_color)
        zox_sys_o(TextureData, textureData)
        zox_sys_o(GenerateTexture, generateTexture)
        zox_sys_o(TextureDirty, textureDirty)
        if (generateTexture->value != zox_generate_texture_generate) {
            continue;
        }
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_texture_fill(textureData->value, textureSize->value, fill_color->value);
        textureDirty->value = 1; // actually this only gets uploaded if has GPUTextureLink!
    }
} zox_declare_system(FillTextureSystem)
