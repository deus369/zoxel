// #define zox_time_frame_texture_system
void FrameTextureSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_field_out(GenerateTexture, generateTextures, 2)
    zox_field_in(TextureSize, textureSizes, 3)
    zox_field_in(Color, colors, 4)
    zox_field_in(OutlineThickness, outlineThicknesss, 5)
    zox_field_in(FrameCorner, frameEdges, 6)
    zox_field_out(TextureData, textureDatas, 7)
    zox_field_out(TextureDirty, textureDirtys, 8)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(GenerateTexture, generateTextures, generateTexture)
        if (!generateTexture->value) continue;
        zox_field_i_out(TextureDirty, textureDirtys, textureDirty)
        // if (textureDirty->value) continue;
        zox_field_e()
        zox_field_i_in(TextureSize, textureSizes, textureSize)
        zox_field_i_in(Color, colors, color2)
        zox_field_i_in(OutlineThickness, outlineThicknesss, outlineThickness)
        zox_field_i_in(FrameCorner, frameEdges, frameEdge)
        zox_field_i_out(TextureData, textureDatas, textureData)
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        const unsigned char add_noise = zox_has(e, TextureAddNoise);
        const color fill_color = color2->value;
        color outline_color;
        if (zox_has(e, OutlineColor)) outline_color = zox_get_value(e, OutlineColor)
        else outline_color = (color) { fill_color.g + 25 + rand() % 25, fill_color.b + 25 + rand() % 25, fill_color.r + 25 + rand() % 25, 255 };
        if (zox_has(e, IconTexture)) generate_texture_icon(textureData->value, textureData->length, textureSize->value, fill_color, outline_color, outlineThickness->value, frameEdge->value, add_noise);
        else generate_texture_frame(textureData->value, textureData->length, textureSize->value, fill_color, outline_color, outlineThickness->value, frameEdge->value, add_noise);
        generateTexture->value = 0;
        textureDirty->value = 1;
    }
} zox_declare_system(FrameTextureSystem)
