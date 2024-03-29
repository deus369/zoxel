// #define zox_time_frame_texture_system

unsigned char check_texture(TextureData* textureData, const TextureSize *textureSize, int2 pixel_position, color find_color, int distance) {
    if (!int2_in_bounds(pixel_position, textureSize->value)) return 0;
    if (color_equal(find_color, textureData->value[int2_array_index(pixel_position, textureSize->value)])) return 1;
    if (distance >= 0) {
        distance--;
        if (check_texture(textureData, textureSize, int2_down(pixel_position), find_color, distance)) return 1;
        if (check_texture(textureData, textureSize, int2_up(pixel_position), find_color, distance)) return 1;
        if (check_texture(textureData, textureSize, int2_left(pixel_position), find_color, distance)) return 1;
        if (check_texture(textureData, textureSize, int2_right(pixel_position), find_color, distance)) return 1;
    }
    return 0;
}

void generate_frame_texture(TextureData* textureData, const TextureSize *textureSize, const Color *color2, unsigned char frame_thickness, unsigned char corner_size) {
    color fill_color = color2->value;
    color outline_color = { fill_color.g + 25 + rand() % 25, fill_color.b + 25 + rand() % 25, fill_color.r + 25 + rand() % 25, 255 };
    color empty = { 0, 0, 0, 0 };
    int index = 0;
    int2 pixel_position = { 0, 0 };
    for (pixel_position.y = 0; pixel_position.y < textureSize->value.y; pixel_position.y++) {
        for (pixel_position.x = 0; pixel_position.x < textureSize->value.x; pixel_position.x++) {
            int distance_to_corner_a = pixel_position.x + pixel_position.y;
            int distance_to_corner_b = (textureSize->value.x - 1 - pixel_position.x) + pixel_position.y;
            int distance_to_corner_c = (textureSize->value.x - 1 - pixel_position.x) + (textureSize->value.y - 1 - pixel_position.y);
            int distance_to_corner_d = pixel_position.x + (textureSize->value.y - 1 - pixel_position.y);
            if (distance_to_corner_a < corner_size || distance_to_corner_b < corner_size || distance_to_corner_c < corner_size || distance_to_corner_d < corner_size) {
                textureData->value[index] = empty;
            } else {
                textureData->value[index] = fill_color;
            }
            index++;
        }
    }
    // outline of frame
    index = 0;
    for (pixel_position.y = 0; pixel_position.y < textureSize->value.y; pixel_position.y++) {
        for (pixel_position.x = 0; pixel_position.x < textureSize->value.x; pixel_position.x++) {
            if (!color_equal(textureData->value[index], fill_color)) {
                index++;
                continue;
            }
            if (pixel_position.x < frame_thickness || pixel_position.y < frame_thickness || pixel_position.x > textureSize->value.x - 1 - frame_thickness || pixel_position.y > textureSize->value.y - 1 - frame_thickness) {
                textureData->value[index] = outline_color;
            }
            // only floodfill check corners of the texture to save processing time
            else if ((pixel_position.x < corner_size && pixel_position.y < corner_size) ||
                (pixel_position.x > textureSize->value.x - corner_size && pixel_position.y < corner_size) ||
                (pixel_position.x > textureSize->value.x - corner_size && pixel_position.y > textureSize->value.y - corner_size) ||
                (pixel_position.x < corner_size && pixel_position.y > textureSize->value.y - corner_size)) {
                if (check_texture(textureData, textureSize, pixel_position, empty, frame_thickness)) {
                    textureData->value[index] = outline_color;
                }
            }
            index++;
        }
    }
    // add noise to fill parts
    index = 0;
    const int fill_noise_addition = 55;
    const int outline_noise_addition = 25;
    for (pixel_position.y = 0; pixel_position.y < textureSize->value.y; pixel_position.y++) {
        for (pixel_position.x = 0; pixel_position.x < textureSize->value.x; pixel_position.x++) {
            if (color_equal(textureData->value[index], fill_color)) {
                textureData->value[index].r += rand() % fill_noise_addition;
                textureData->value[index].g += rand() % fill_noise_addition;
                textureData->value[index].b += rand() % fill_noise_addition;
            } else if (color_equal(textureData->value[index], outline_color)) {
                textureData->value[index].r += rand() % outline_noise_addition;
                textureData->value[index].g += rand() % outline_noise_addition;
                textureData->value[index].b += rand() % outline_noise_addition;
            }
            index++;
        }
    }
}

void FrameTextureSystem(ecs_iter_t *it) {
    if (!it->ctx || !ecs_query_changed(it->ctx, NULL)) return;
    #ifdef zox_time_frame_texture_system
        begin_timing()
    #endif
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    const Color *colors = ecs_field(it, Color, 4);
    const OutlineThickness *outlineThicknesss = ecs_field(it, OutlineThickness, 5);
    const FrameCorner *frameEdges = ecs_field(it, FrameCorner, 6);
    TextureData *textures = ecs_field(it, TextureData, 7);
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 8);
    for (int i = 0; i < it->count; i++) {
        GenerateTexture *generateTexture = &generateTextures[i];
        if (!generateTexture->value) continue;
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value) continue;
        const TextureSize *textureSize = &textureSizes[i];
        const Color *color2 = &colors[i];
        const OutlineThickness *outlineThickness = &outlineThicknesss[i];
        const FrameCorner *frameEdge = &frameEdges[i];
        TextureData *textureData = &textures[i];
        resize_memory_component(TextureData, textureData, color, textureSize->value.x * textureSize->value.y)
        generate_frame_texture(textureData, textureSize, color2, outlineThickness->value, frameEdge->value);
        generateTexture->value = 0;
        textureDirty->value = 1;
        #ifdef zox_time_frame_texture_system
            did_do_timing()
        #endif
        // zox_log("   > texture (frame) generated [%i] - %lu - %f\n", i, it->entities[i], zox_current_time)
    }
    #ifdef zox_time_frame_texture_system
        end_timing("    - frame_texture_system")
    #endif
} zox_declare_system(FrameTextureSystem)


/* || color_equal(textureData->value[int2_array_index(int2_down(pixel_position), textureSize->value)], empty) ||
color_equal(textureData->value[int2_array_index(int2_up(pixel_position), textureSize->value)], empty) ||
color_equal(textureData->value[int2_array_index(int2_left(pixel_position), textureSize->value)], empty) ||
color_equal(textureData->value[int2_array_index(int2_right(pixel_position), textureSize->value)], empty)*/
//if (j <= corner_size || j >= textureSize->value.x - 1 - corner_size
//    || k <= corner_size || k >= textureSize->value.y - 1 - corner_size)
/*else if (j <= frame_thickness || k <= frame_thickness || j >= textureSize->value.x - 1 - frame_thickness || k >= textureSize->value.y - 1 - frame_thickness)
{
    textureData->value[index] = darker;
}*/
    /*const int2 redRange = { 15, 244 };
    const int2 greenRange = { 15, 122 };
    const int2 blueRange = { 15, 122 };
    const int2 alphaRange = { 144, 256 };
    const int2 alphaRange2 = { 222, 256 };
    color fill_color = { 
        redRange.x + rand() % (redRange.y - redRange.x),
        greenRange.x + rand() % (greenRange.y - greenRange.x),
        blueRange.x + rand() % (blueRange.y - blueRange.x),
        alphaRange.x + rand() % (alphaRange.y - alphaRange.x)
    };
    color outline_color = { 
        redRange.x + rand() % (redRange.y - redRange.x),
        greenRange.x + rand() % (greenRange.y - greenRange.x),
        blueRange.x + rand() % (blueRange.y - blueRange.x),
        alphaRange2.x + rand() % (alphaRange2.y - alphaRange2.x)
    };*/
