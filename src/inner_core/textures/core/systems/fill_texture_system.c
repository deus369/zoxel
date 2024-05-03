// simple system
void FillTextureSystem(ecs_iter_t *it) {
    zox_change_check()
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 2);
    TextureData *textures = ecs_field(it, TextureData, 3);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 4);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 5);
    const Color *colors = ecs_field(it, Color, 6);
    for (int i = 0; i < it->count; i++) {
        GenerateTexture *generateTexture = &generateTextures[i];
        if (!generateTexture->value) continue;
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value) continue;
        const TextureSize *textureSize = &textureSizes[i];
        TextureData *textureData = &textures[i];
        const Color *color2 = &colors[i];
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_texture_fill(textureData, textureSize->value, color2->value);
        generateTexture->value = 0;
        textureDirty->value = 1; // actually this only gets uploaded if has GPUTextureLink!
    }
} zox_declare_system(FillTextureSystem)
