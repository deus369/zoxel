void generate_font_texture(TextureData* textureData, const TextureSize *textureSize, const FontData *fontData, const Color *color2) {
    const unsigned char is_background = 0;
    const color nothing = { 0, 0, 0, 0 };
    const int frame_thickness = textureSize->value.x / 4;
    const int2 redRange = { 15, 244 };
    const int2 greenRange = { 15, 122 };
    const int2 blueRange = { 15, 122 };
    const int2 alphaRange = { 144, 256 };
    const int2 alphaRange2 = { 222, 256 };
    color base = { 
        redRange.x + rand() % (redRange.y - redRange.x),
        greenRange.x + rand() % (greenRange.y - greenRange.x),
        blueRange.x + rand() % (blueRange.y - blueRange.x),
        alphaRange.x + rand() % (alphaRange.y - alphaRange.x)
    };
    color darker = { 
        redRange.x + rand() % (redRange.y - redRange.x),
        greenRange.x + rand() % (greenRange.y - greenRange.x),
        blueRange.x + rand() % (blueRange.y - blueRange.x),
        alphaRange2.x + rand() % (alphaRange2.y - alphaRange2.x)
    };
    // color font_color = (color) { 5 + rand() % 120, 100 + rand() % 120, 100 + rand() % 120, 255 };
    color font_color = color2->value; // (color) { 55, 185, 125, 255 };
    int index = 0;
    for (int k = 0; k < textureSize->value.y; k++) {
        for (int j = 0; j < textureSize->value.x; j++) {
            if (!is_background) {
                textureData->value[index] = nothing;
            } else if (j <= frame_thickness || k <= frame_thickness || j >= textureSize->value.x - 1 - frame_thickness || k >= textureSize->value.y - 1 - frame_thickness) {
                textureData->value[index] = base;
            } else {
                textureData->value[index] = darker;
            }
            index++;
        }
    }
    // point A to B - use FontData byte2 data.
    for (int i = 0; i < fontData->length; i += 2) {
        int2 pointA = byte2_to_int2(fontData->value[i]);
        int2 pointB = byte2_to_int2(fontData->value[i + 1]);
        #ifdef debug_font_texture
            zoxel_log("Font Data %i %ix%i > %ix%i\n", i, pointA.x, pointA.y, pointB.x, pointB.y);
        #endif
        pointA.x = (int) ((pointA.x / 255.0f) * textureSize->value.x);
        pointA.y = (int) ((pointA.y / 255.0f) * textureSize->value.y);
        pointB.x = (int) ((pointB.x / 255.0f) * textureSize->value.x);
        pointB.y = (int) ((pointB.y / 255.0f) * textureSize->value.y);
        int distance = int2_distance(pointA, pointB);
        float2 direction = float2_normalize(float2_sub(int2_to_float2(pointB), int2_to_float2(pointA)));
        #ifdef debug_font_texture
            zoxel_log("    - %ix%i > %ix%i\n", pointA.x, pointA.y, pointB.x, pointB.y);
            zoxel_log("    - distance %i direction %fx%f\n", distance, direction.x, direction.y);
        #endif
        int2 splash_point = pointA;
        for (int j = 0; j <= distance; j++) {
            int2 splash_point_check = int2_add(float2_to_int2(float2_multiply_float(direction, (float) j)), pointA);
            if (int2_equal(splash_point, splash_point_check)) continue;
            splash_point = splash_point_check;
            // add noise later to this
            int pointSize2 = 1 + rand() % 1; // math.floor(random.NextFloat(pointSize.x, pointSize.y));
            #ifdef debug_font_texture
                zoxel_log("    - j %i splash_point %ix%i size %i\n", j, splash_point.x, splash_point.y, pointSize2);
            #endif
            for (int k = -pointSize2; k <= pointSize2; k++) {
                for (int l = -pointSize2; l <= pointSize2; l++) {
                    int2 drawPoint = (int2) { splash_point.x + k, splash_point.y + l};
                    if (drawPoint.x >= 0 && drawPoint.x < textureSize->value.x
                        && drawPoint.y >= 0 && drawPoint.y < textureSize->value.y) {
                        textureData->value[int2_array_index(drawPoint, textureSize->value)] = font_color;
                    }
                }
            }
            j += int_clamp(pointSize2, 0, pointSize2 - 1); // (int) math.clamp(pointSize2, 0, pointSize2 - 1);
        }
    }
}

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
            zoxel_log("     > zigel font is updating [%lu]\n", (long int) it->entities[i]);
        #endif
    }
} zox_declare_system(FontTextureSystem)

/*(int2) {
    random.NextFloat(pointNoise.x * 2) - pointNoise.x, 
    random.NextFloat(pointNoise.y * 2) - pointNoise.y };*/