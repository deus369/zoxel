// #define zox_time_frame_texture_system
void FrameTextureSystem(ecs_iter_t *it) {
    zox_change_check()
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TextureSize)
    zox_sys_in(Color)
    zox_sys_in(OutlineThickness)
    zox_sys_in(FrameCorner)
    zox_sys_out(GenerateTexture)
    zox_sys_out(TextureData)
    zox_sys_out(TextureDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(TextureSize, textureSize)
        zox_sys_i(Color, color2)
        zox_sys_i(OutlineThickness, outlineThickness)
        zox_sys_i(FrameCorner, frameEdge)
        zox_sys_o(TextureData, textureData)
        zox_sys_o(TextureDirty, textureDirty)
        zox_sys_o(GenerateTexture, generateTexture)
        if (generateTexture->value != zox_generate_texture_generate) {
            continue;
        }
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        const byte add_noise = zox_has(e, TextureAddNoise);
        const color fill_color = color2->value;
        color outline_color;
        if (zox_has(e, OutlineColor)) {
            outline_color = zox_get_value(e, OutlineColor)
        } else {
            outline_color = (color) {
                fill_color.g + 25 + rand() % 25,
                fill_color.b + 25 + rand() % 25,
                fill_color.r + 25 + rand() % 25,
                255
            };
        }
        if (zox_has(e, IconTexture)) {
            const byte radius = (byte ) (textureSize->value.y * zox_gett_value(e, IconRadius));
            generate_texture_icon(textureData->value, textureData->length, textureSize->value, fill_color, outline_color, outlineThickness->value, radius, add_noise);
            // zox_log(" > [%s] radius [%i] size [%ix%i]\n", zox_get_name(it->entities[i]), radius, textureSize->value.x, textureSize->value.y)
        } else {
            generate_texture_frame(
                textureData->value,
                textureData->length,
                textureSize->value,
                fill_color,
                outline_color,
                outlineThickness->value,
                frameEdge->value,
                add_noise);
        }
        // zox_log("+ texture generated [%s]", zox_get_name(e))
        textureDirty->value = 1;
        //  voronoi2D(textureData->value, textureSize->value, color_gray, color_gray_dark, 0.7f);
    }
} zox_declare_system(FrameTextureSystem)