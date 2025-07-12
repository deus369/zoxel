void FontTextureSystem(ecs_iter_t *it) {
    const color air_color = (color) { 0, 0, 0, 0 };
    const float2 point_padding = font_point_padding;
    // const byte default_font_outline = 1; // 4
    zox_change_check()
    zox_field_world()
    // todo: link each zigel to fontstyle's font
    ecs_entity_t zox_font_style = get_font_style_using();
    if (!zox_font_style || !zox_has(zox_font_style, Children)) {
        return;
    }
    zox_geter(zox_font_style, Children, font_style_children)
    if (!font_style_children) {
        zox_log("! font_style_children is NULL\n")
        return;
    }
    const byte is_use_shapes = zox_has(zox_font_style, TTFFontStyle);
    zox_sys_begin()
    zox_sys_in(ZigelIndex)
    zox_sys_in(Color)
    zox_sys_in(SecondaryColor)
    zox_sys_in(TextureSize)
    zox_sys_in(FontThickness)
    zox_sys_in(FontOutlineThickness)
    zox_sys_out(TextureData)
    zox_sys_out(TextureDirty)
    zox_sys_out(GenerateTexture)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ZigelIndex, zigelIndex)
        zox_sys_i(TextureSize, textureSize)
        zox_sys_i(Color, color_variable)
        zox_sys_i(SecondaryColor, secondaryColor)
        zox_sys_i(FontThickness, fontThickness)
        zox_sys_i(FontOutlineThickness, fontOutlineThickness)
        zox_sys_o(GenerateTexture, generateTexture)
        zox_sys_o(TextureDirty, textureDirty)
        zox_sys_o(TextureData, textureData)
        if (generateTexture->value != zox_generate_texture_generate || textureDirty->value != 0 || zigelIndex->value >= font_styles_length) {
            continue;
        }
        // get font based on zigel index
        const ecs_entity_t font = font_style_children->value[zigelIndex->value];
        int length = textureSize->value.x * textureSize->value.y;
        if (length <= 0 || fontThickness->value == 0 || !zox_valid(font)) {
            if (length <= 0) {
                length = 1;
            }
            resize_memory_component(TextureData, textureData, color, length)
            for (int j = 0; j < length; j++) {
                textureData->value[j] = air_color;
            }
            textureDirty->value = 1;
            continue;
        }
        zox_geter(font, FontData, fontData)
        resize_memory_component(TextureData, textureData, color, length)
        generate_font_texture(textureData->value, textureSize->value, fontData, secondaryColor->value, color_variable->value, is_use_shapes, fontThickness->value, fontOutlineThickness->value, point_padding);
        generateTexture->value = 0;
        textureDirty->value = 1;
#ifdef zoxel_debug_zigel_updates
        zox_log("     > zigel font is updating [%lu]\n", it->entities[i])
#endif
    }
} zox_declare_system(FontTextureSystem)