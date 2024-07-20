void FontTextureSystem(ecs_iter_t *it) {
    const color air_color = (color) { 0, 0, 0, 0 };
    zox_change_check()
    // todo: link each zigel to fontstyle's font
    ecs_entity_t zox_font_style = get_font_style_using();
    if (!zox_font_style || !zox_has(zox_font_style, Children)) return;
    zox_iter_world()
    zox_field_in(ZigelIndex, zigelIndexs, 1)
    zox_field_in(Color, colors, 2)
    zox_field_in(SecondaryColor, secondaryColors, 3)
    zox_field_in(TextureSize, textureSizes, 4)
    zox_field_out(FontThickness, fontThicknesss, 5)
    zox_field_out(TextureData, textureDatas, 6)
    zox_field_out(TextureDirty, textureDirtys, 7)
    zox_field_out(GenerateTexture, generateTextures, 8)
    const Children *font_style_children = zox_get(zox_font_style, Children)
    const unsigned char is_use_shapes = zox_has(zox_font_style, TTFFontStyle);
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateTexture, generateTextures, generateTexture)
        if (generateTexture->value != zox_generate_texture_generate) continue;
        zox_field_o(TextureDirty, textureDirtys, textureDirty)
        if (textureDirty->value != 0) continue;
        zox_field_i(ZigelIndex, zigelIndexs, zigelIndex)
        if (zigelIndex->value >= font_styles_length) continue;
        zox_field_i(TextureSize, textureSizes, textureSize)
        zox_field_i(Color, colors, color_variable)
        zox_field_i(SecondaryColor, secondaryColors, secondaryColor)
        zox_field_i(FontThickness, fontThicknesss, fontThickness)
        zox_field_o(TextureData, textureDatas, textureData)
        // get font based on zigel index
        const ecs_entity_t font = font_style_children->value[zigelIndex->value];
        if (!font) { // spacece
            const int length = textureSize->value.x * textureSize->value.y;
            resize_memory_component(TextureData, textureData, color, length)
            for (int j = 0; j < length; j++) textureData->value[j] = air_color;
            // generateTexture->value = 0;
            textureDirty->value = 1;
            continue;
        }
        const FontData *fontData = zox_get(font, FontData)
        const int length = textureSize->value.x * textureSize->value.y;
        resize_memory_component(TextureData, textureData, color, length)
        generate_font_texture(textureData->value, textureSize->value, fontData, secondaryColor->value, color_variable->value, is_use_shapes, fontThickness->value);
        generateTexture->value = 0;
        textureDirty->value = 1;
#ifdef zoxel_debug_zigel_updates
        zox_log("     > zigel font is updating [%lu]\n", it->entities[i])
#endif
    }
} zox_declare_system(FontTextureSystem)
