const color empty_color = { 0, 0, 0, 0 };

// move this to prefab
void add_frame_texture_type(ecs_world_t *world, ecs_entity_t e, color primary, unsigned char corner, unsigned char thickness) {
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { corner })
    zox_prefab_set(e, OutlineThickness, { thickness })
    zox_prefab_set(e, Color, { primary })
}

unsigned char check_texture(const color *data, const int2 size, const int2 pixel_position, const color find_color, int distance) {
    if (!int2_in_bounds(pixel_position, size)) return 0;
    if (color_equal(find_color, data[int2_array_index(pixel_position, size)])) return 1;
    if (distance >= 0) {
        distance--;
        if (check_texture(data, size, int2_down(pixel_position), find_color, distance)) return 1;
        if (check_texture(data, size, int2_up(pixel_position), find_color, distance)) return 1;
        if (check_texture(data, size, int2_left(pixel_position), find_color, distance)) return 1;
        if (check_texture(data, size, int2_right(pixel_position), find_color, distance)) return 1;
    }
    return 0;
}

void generate_texture_icon(color *data, const int length, const int2 size, const color fill_color, const color outline_color, const unsigned char frame_thickness, const unsigned char radius, const unsigned char is_noise) {
    int index = 0;
    int2 mid_position = int2_half(size);
    int2 pixel_position = { 0, 0 };
    for (pixel_position.y = 0; pixel_position.y < size.y; pixel_position.y++) {
        for (pixel_position.x = 0; pixel_position.x < size.x; pixel_position.x++) {
            const int distance_to_mid = int2_distance(pixel_position, mid_position);
            if (distance_to_mid < radius) {
                data[index] = fill_color;
            } else if (distance_to_mid == radius) {
                data[index] = outline_color;
            } else {
                data[index] = empty_color;
            }
            index++;
        }
    }
}

void generate_texture_frame(color *data, const int length, const int2 size, const color fill_color, const color outline_color, const unsigned char frame_thickness, const unsigned char corner_size, const unsigned char is_noise) {
    int index = 0;
    int2 pixel_position = { 0, 0 };
    for (pixel_position.y = 0; pixel_position.y < size.y; pixel_position.y++) {
        for (pixel_position.x = 0; pixel_position.x < size.x; pixel_position.x++) {
            int distance_to_corner_a = pixel_position.x + pixel_position.y;
            int distance_to_corner_b = (size.x - 1 - pixel_position.x) + pixel_position.y;
            int distance_to_corner_c = (size.x - 1 - pixel_position.x) + (size.y - 1 - pixel_position.y);
            int distance_to_corner_d = pixel_position.x + (size.y - 1 - pixel_position.y);
            if (distance_to_corner_a < corner_size || distance_to_corner_b < corner_size || distance_to_corner_c < corner_size || distance_to_corner_d < corner_size) {
                data[index] = empty_color;
            } else {
                data[index] = fill_color;
            }
            index++;
        }
    }
    // outline of frame
    index = 0;
    for (pixel_position.y = 0; pixel_position.y < size.y; pixel_position.y++) {
        for (pixel_position.x = 0; pixel_position.x < size.x; pixel_position.x++) {
            if (!color_equal(data[index], fill_color)) {
                index++;
                continue;
            }
            if (pixel_position.x < frame_thickness || pixel_position.y < frame_thickness || pixel_position.x > size.x - 1 - frame_thickness || pixel_position.y > size.y - 1 - frame_thickness) {
                data[index] = outline_color;
            }
            // only floodfill check corners of the texture to save processing time
            else if ((pixel_position.x < corner_size && pixel_position.y < corner_size) ||
                (pixel_position.x > size.x - corner_size && pixel_position.y < corner_size) ||
                (pixel_position.x > size.x - corner_size && pixel_position.y > size.y - corner_size) ||
                (pixel_position.x < corner_size && pixel_position.y > size.y - corner_size)) {
                if (check_texture(data, size, pixel_position, empty_color, frame_thickness)) {
                    data[index] = outline_color;
                }
            }
            index++;
        }
    }
    // add noise to fill parts
    if (is_noise) {
        index = 0;
        const int fill_noise_addition = 55;
        const int outline_noise_addition = 25;
        for (pixel_position.y = 0; pixel_position.y < size.y; pixel_position.y++) {
            for (pixel_position.x = 0; pixel_position.x < size.x; pixel_position.x++) {
                if (color_equal(data[index], fill_color)) {
                    data[index].r += rand() % fill_noise_addition;
                    data[index].g += rand() % fill_noise_addition;
                    data[index].b += rand() % fill_noise_addition;
                } else if (color_equal(data[index], outline_color)) {
                    data[index].r += rand() % outline_noise_addition;
                    data[index].g += rand() % outline_noise_addition;
                    data[index].b += rand() % outline_noise_addition;
                }
                index++;
            }
        }
    }
}

void generate_texture_fill(TextureData* textureData, const int2 size, const color fill_color) {
    int2 position;
    for (position.x = 0; position.x < size.x; position.x++)
        for (position.y = 0; position.y < size.y; position.y++)
            textureData->value[int2_array_index(position, size)] = fill_color;
}

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

void generate_texture_noise(TextureData* textureData, const TextureSize *textureSize, unsigned char texture_type, unsigned char outline_type) {
    int2 redRange = { 15, 244 };
    int2 greenRange = { 15, 122 };
    int2 blueRange = { 15, 122 };
    int2 alphaRange = { 144, 256 };
    if (texture_type != zox_texture_none) {
        redRange = (int2) { 53, 93 };  // 73
        greenRange = (int2) { 37, 57 };  // 47
        blueRange = (int2) { 7, 27 };  // 17
        alphaRange = (int2) { 255, 256 };
        // if (rand() % 100 >= 50) {
        if (texture_type == zox_texture_dirt) {
            redRange.x += 16;
            redRange.y += 32;
            greenRange.x += 8;
            greenRange.y += 16;
            blueRange.x += 8;
            blueRange.y += 16;
        } else if (texture_type == zox_texture_grass) {
            greenRange.x *= 2;
            greenRange.y *= 2;
            blueRange.x = redRange.x - 30;
            blueRange.y = redRange.y - 30;
            redRange.x /= 2;
            redRange.y /= 2;
        } else if (texture_type == zox_texture_sand) {
            redRange.x = redRange.y = 206 - 50;
            greenRange.x = greenRange.y = 179 - 50;
            blueRange.x = blueRange.y = 59 - 30;
            redRange.x -= 10 + rand() % 30;
            greenRange.x -= 10 + rand() % 30;
            blueRange.x -= 10 + rand() % 20;
        } else if (texture_type == zox_texture_stone) {
            redRange.x = redRange.y = 100;
            greenRange.x = greenRange.y = 100;
            blueRange.x = blueRange.y = 100;
            redRange.x -= 10 + rand() % 20;
            greenRange.x -= 10 + rand() % 20;
            blueRange.x -= 10 + rand() % 20;
        } else if (zox_texture_obsidian) {
            redRange.x = redRange.y = 42;
            greenRange.x = greenRange.y = 42;
            blueRange.x = blueRange.y = 42;
            redRange.x -= 6 + rand() % 12;
            greenRange.x -= 6 + rand() % 12;
            blueRange.x -= 6 + rand() % 12;
        }
    }
    if (texture_type == zox_texture_graybox) {
        generate_texture_graybox(textureData, textureSize, int2_zero, textureSize->value);
        //generate_texture_graybox(textureData, textureSize, (int2) { 0, 0 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
        //generate_texture_graybox(textureData, textureSize, (int2) { textureSize->value.x / 2, 0 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
        //generate_texture_graybox(textureData, textureSize, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
        //generate_texture_graybox(textureData, textureSize, (int2) { 0, textureSize->value.y / 2 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
    } else {
        for (int j = 0; j < textureSize->value.x; j++) {
            for (int k = 0; k < textureSize->value.y; k++) {
                int index = j + k * textureSize->value.x;
                if (texture_type == zox_texture_none) {
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
                /*if (j >= textureSize->value.x / 2 && k < textureSize->value.y / 2) {
                    textureData->value[index].g *= 2;
                    textureData->value[index].b = textureData->value[index].r - 30;
                    textureData->value[index].r /= 2;
                }*/
                // textureData->value[index].a = rand() % 256;
                // debug sides of textureData, starts at top left
                if (texture_type == zox_texture_none) {
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
                }
                if (outline_type == zox_outline_type_full) {
                    // outline voxel textures
                    if (j == 0 || k == 0 || j == textureSize->value.x - 1 || k == textureSize->value.y - 1) {
                        textureData->value[index].r = 0;
                        textureData->value[index].g = 0;
                        textureData->value[index].b = 0;
                    }
                } else if (outline_type == zox_outline_type_half) {
                    if (j == 0 || k == 0 || j == textureSize->value.x - 1 || k == textureSize->value.y - 1) {
                        textureData->value[index].r /= 2;
                        textureData->value[index].g /= 2;
                        textureData->value[index].b /= 2;
                    }
                } else if (outline_type == zox_outline_type_faded) {
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
    }
}
