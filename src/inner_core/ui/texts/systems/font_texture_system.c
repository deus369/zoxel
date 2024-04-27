void FontTextureSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(it->ctx, NULL)) return;
    const Children *font_style_children = ecs_get(world, font_style_entity, Children);
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 2);
    TextureData *textures = ecs_field(it, TextureData, 3);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 4);
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 5);
    const ZigelIndex *zigelIndexs = ecs_field(it, ZigelIndex, 6);
    const Color *colors = ecs_field(it, Color, 7);
    for (int i = 0; i < it->count; i++) {
        GenerateTexture *generateTexture = &generateTextures[i];
        if (generateTexture->value == 0) continue;
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value != 0) continue;
        // get font based on zigel index
        const ZigelIndex *zigelIndex = &zigelIndexs[i];
        if (zigelIndex->value >= font_styles_length) continue;
        TextureData *textureData = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        const Color *color2 = &colors[i];
        ecs_entity_t zigel_font_entity = font_style_children->value[zigelIndex->value];
        const FontData *fontData = ecs_get(world, zigel_font_entity, FontData);
        int newLength = textureSize->value.x * textureSize->value.y;
        resize_memory_component(TextureData, textureData, color, newLength)
        generate_font_texture(textureData, textureSize, fontData, color2);
        textureDirty->value = 1;
        generateTexture->value = 0;
#ifdef zoxel_debug_zigel_updates
        zox_log("     > zigel font is updating [%lu]\n", it->entities[i])
#endif
    }
} zox_declare_system(FontTextureSystem)

/*(int2) {
    random.NextFloat(pointNoise.x * 2) - pointNoise.x, 
    random.NextFloat(pointNoise.y * 2) - pointNoise.y };*/
