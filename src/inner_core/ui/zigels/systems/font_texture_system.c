void FontTextureSystem(ecs_iter_t *it) {
    const color air_color = (color) { 0, 0, 0, 0 };
    // const color fill_color = (color) { 22, 255, 122, 222 };
    // const color fill_color = (color) { 44, 66, 66, 222 };
    zox_change_check()
    // todo: link each zigel to fontstyle's font
    if (!zox_font_style || !zox_has(zox_font_style, Children)) return;
    zox_iter_world()
    const Children *font_style_children = zox_get(zox_font_style, Children)
    zox_field_in(ZigelIndex, zigelIndexs, 1)
    zox_field_in(Color, colors, 2)
    zox_field_in(SecondaryColor, secondaryColors, 3)
    zox_field_in(TextureSize, textureSizes, 4)
    zox_field_out(TextureData, textureDatas, 5)
    zox_field_out(TextureDirty, textureDirtys, 6)
    zox_field_out(GenerateTexture, generateTextures, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(GenerateTexture, generateTextures, generateTexture)
        if (generateTexture->value == 0) continue;
        zox_field_i_out(TextureDirty, textureDirtys, textureDirty)
        if (textureDirty->value != 0) continue;
        zox_field_i_in(ZigelIndex, zigelIndexs, zigelIndex)
        if (zigelIndex->value >= font_styles_length) continue;
        zox_field_i_out(TextureData, textureDatas, textureData)
        zox_field_i_in(TextureSize, textureSizes, textureSize)
        zox_field_i_in(Color, colors, color_variable)
        zox_field_i_in(SecondaryColor, secondaryColors, secondaryColor)
        // get font based on zigel index
        const ecs_entity_t font = font_style_children->value[zigelIndex->value];
        if (!font) { // spacece
            const int length = textureSize->value.x * textureSize->value.y;
            resize_memory_component(TextureData, textureData, color, length)
            for (int j = 0; j < length; j++) textureData->value[j] = air_color;
            generateTexture->value = 0;
            textureDirty->value = 1;
            continue;
        }
        const FontData *fontData = zox_get(font, FontData)
        const int length = textureSize->value.x * textureSize->value.y;
        resize_memory_component(TextureData, textureData, color, length)
        generate_font_texture(textureData, textureSize->value, fontData, color_variable->value, secondaryColor->value);
        generateTexture->value = 0;
        textureDirty->value = 1;
#ifdef zoxel_debug_zigel_updates
        zox_log("     > zigel font is updating [%lu]\n", it->entities[i])
#endif
    }
} zox_declare_system(FontTextureSystem)

/*(int2) {
    random.NextFloat(pointNoise.x * 2) - pointNoise.x, 
    random.NextFloat(pointNoise.y * 2) - pointNoise.y };*/
