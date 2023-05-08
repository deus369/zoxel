void generate_texture_graybox(TextureData* textureData, const TextureSize *textureSize, int2 position, int2 size) {
    for (int j = position.x; j < position.x + size.x; j++) {
        for (int k = position.y; k < position.y + size.y; k++) {
            int index = j + k * textureSize->value.x;
            if (j == position.x || k == position.y || j == position.x + size.x - 1 || k == position.y + size.y - 1) {
                textureData->value[index].r = 0;
                textureData->value[index].g = 0;
                textureData->value[index].b = 0;
            } else {
                textureData->value[index].r = 125;
                textureData->value[index].g = 125;
                textureData->value[index].b = 125;
            }
        }
    }
}

//! Our function that creates a textureData.
void GenerateNoise(TextureData* textureData, const TextureSize *textureSize, unsigned char is_dirt) {
    int2 redRange = { 15, 244 };
    int2 greenRange = { 15, 122 };
    int2 blueRange = { 15, 122 };
    int2 alphaRange = { 144, 256 };
    if (is_dirt) {
        redRange = (int2) { 53, 93 };  // 73
        greenRange = (int2) { 37, 57 };  // 47
        blueRange = (int2) { 7, 27 };  // 17
        alphaRange = (int2) { 255, 256 };
    }
    #ifdef zox_grayboxing
        generate_texture_graybox(textureData, textureSize, (int2) { 0, 0 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
        generate_texture_graybox(textureData, textureSize, (int2) { textureSize->value.x / 2, 0 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
        generate_texture_graybox(textureData, textureSize, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
        generate_texture_graybox(textureData, textureSize, (int2) { 0, textureSize->value.y / 2 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
    #else
    for (int j = 0; j < textureSize->value.x; j++) {
        for (int k = 0; k < textureSize->value.y; k++) {
            int index = j + k * textureSize->value.x;
            if (!is_dirt) {
                int distanceToMidX = abs_integer(textureSize->value.x / 2 - j);
                int distanceToMidY = abs_integer(textureSize->value.y / 2 - k);
                if (distanceToMidX + distanceToMidY >= textureSize->value.x / 2) {
                    textureData->value[index].r = 0;
                    textureData->value[index].g = 0;
                    textureData->value[index].b = 0;
                    textureData->value[index].a = 0;
                    continue;
                }
            }
            textureData->value[index].r = redRange.x + rand() % (redRange.y - redRange.x);
            textureData->value[index].g = greenRange.x + rand() % (greenRange.y - greenRange.x);
            textureData->value[index].b = blueRange.x + rand() % (blueRange.y - blueRange.x);
            textureData->value[index].a = alphaRange.x + rand() % (alphaRange.y - alphaRange.x);
            if (j >= textureSize->value.x / 2 && k < textureSize->value.y / 2) {
                textureData->value[index].g *= 2;
                textureData->value[index].b = textureData->value[index].r - 30;
                textureData->value[index].r /= 2;
            }
            // textureData->value[index].a = rand() % 256;
            // debug sides of textureData, starts at top left
            if (!is_dirt) {
                if (j == 0) {
                    textureData->value[index].r = 255;
                } else if (k == 0) {
                    textureData->value[index].g = 255;
                } else if (j == textureSize->value.x - 1) {
                    textureData->value[index].b = 255;
                } else if (k == textureSize->value.y - 1) {
                    textureData->value[index].r = 255;
                    textureData->value[index].g = 255;
                }
            } else if (is_texture_outlines == 1) {
                // outline voxel textures
                if (j == 0 || k == 0 || j == textureSize->value.x - 1 || k == textureSize->value.y - 1) {
                    textureData->value[index].r = 0;
                    textureData->value[index].g = 0;
                    textureData->value[index].b = 0;
                }
            } else if (is_texture_outlines == 2) {
                if (j == 0 || k == 0 || j == textureSize->value.x - 1 || k == textureSize->value.y - 1) {
                    textureData->value[index].r /= 2;
                    textureData->value[index].g /= 2;
                    textureData->value[index].b /= 2;
                }
            } else if (is_texture_outlines == 3) {
                if (j == 0 || k == 0 || j == textureSize->value.x - 1 || k == textureSize->value.y - 1) {
                    textureData->value[index].r *= 5;
                    textureData->value[index].g *= 5;
                    textureData->value[index].b *= 5;
                    textureData->value[index].r /= 6;
                    textureData->value[index].g /= 6;
                    textureData->value[index].b /= 6;
                }
            }
            // printf("textureData value: %i\n", textureData->value[index].r);
        }
    }
    #endif
}

void NoiseTextureSystem(ecs_iter_t *it) {
    //! This breaks the updates. \todo Fix this. Find out why it doesn't work properly.
    //! This doesn't work because the table writes all changes in the first iteration which is for one entity.
    //!     Possible fix: Make a second system that writes changes at the end of the loop
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL)) {
        return;
    }
    // ecs_iter_t changeIterator = ecs_query_iter(it->world, changeQuery);
    // while (ecs_query_next(&changeIterator));
    // printf("NoiseTextureSystem: [GenerateTexture Changed]\n");
    TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 2);
    TextureData *textures = ecs_field(it, TextureData, 3);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 4);
    const GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 5);
    for (int i = 0; i < it->count; i++) {
        const GenerateTexture *generateTexture = &generateTextures[i];
        //! Only rebuild if GenerateTexture is set to 1 and EntityDirty is false.
        if (generateTexture->value == 0) {
            continue;
        }
        TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value != 0) {
            continue;
        }
        textureDirty->value = 1;
        TextureData *textureData = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        int newLength = textureSize->value.x * textureSize->value.y;
        re_initialize_memory_component(textureData, color, newLength);
        unsigned char is_dirt = ecs_has(it->world, it->entities[i], DirtTexture);
        GenerateNoise(textureData, textureSize, is_dirt);
        // printf("Noise TextureData Generated: [%lu] \n", (long int) it->entities[i]);
    }
}
zoxel_declare_system(NoiseTextureSystem)