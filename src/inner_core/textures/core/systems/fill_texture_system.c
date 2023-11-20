// simple system
void generate_texture_fill(TextureData* textureData, const int2 size, const color fill_color) {
    int2 position;
    for (position.x = 0; position.x < size.x; position.x++)
        for (position.y = 0; position.y < size.y; position.y++)
            textureData->value[int2_array_index(position, size)] = fill_color;
}

void FillTextureSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(it->ctx, NULL)) return;
    // zox_iter_world()
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
        // ecs_entity_t e = it->entities[i];
        const TextureSize *textureSize = &textureSizes[i];
        TextureData *textureData = &textures[i];
        const Color *color2 = &colors[i];
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_texture_fill(textureData, textureSize->value, color2->value); // (color) { 255, 0, 0 }); // 
        generateTexture->value = 0;
        textureDirty->value = 1; // actually this only gets uploaded if has GPUTextureLink!
        // zox_log("   > entity [%lu] filled texture with color [%ix%ix%i]\n", it->entities[i], color2->value.r, color2->value.g, color2->value.b);
    }
} zox_declare_system(FillTextureSystem)
