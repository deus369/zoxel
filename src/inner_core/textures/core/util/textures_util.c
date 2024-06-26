const color empty_color = { 0, 0, 0, 0 };

// move this to prefab
void add_frame_texture_type(ecs_world_t *world, const ecs_entity_t e, const color primary, unsigned char corner, unsigned char thickness) {
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

void generate_texture_fill(color* data, const int2 size, const color fill_color) {
    int2 position;
    for (position.x = 0; position.x < size.x; position.x++)
        for (position.y = 0; position.y < size.y; position.y++)
            data[int2_array_index(position, size)] = fill_color;
}

void generate_texture_graybox(color* data, const int2 big_size, int2 position, const int2 size) {
    for (int j = position.x; j < position.x + size.x; j++) {
        for (int k = position.y; k < position.y + size.y; k++) {
            int index = j + k * big_size.x;
            if (j == position.x || k == position.y || j == position.x + size.x - 1 || k == position.y + size.y - 1) {
                data[index].r = 0;
                data[index].g = 0;
                data[index].b = 0;
            } else {
                data[index].r = 125;
                data[index].g = 125;
                data[index].b = 125;
            }
        }
    }
}

void generate_texture_noise(color* data, const int2 size, const unsigned char texture_type, const unsigned char outline_type, color fill_color) {
    color color_min = { 15, 15, 15, 255 };
    color color_max = { 15, 15, 15, 255 };
    /*int2 redRange = { 15, 244 };
    int2 greenRange = { 15, 122 };
    int2 blueRange = { 15, 122 };
    int2 alphaRange = { 144, 256 };*/
    if (texture_type != zox_texture_none) {
        /*redRange = (int2) { 53, 93 };  // 73
        greenRange = (int2) { 37, 57 };  // 47
        blueRange = (int2) { 7, 27 };  // 17
        alphaRange = (int2) { 255, 256 };*/
        // if (rand() % 100 >= 50) {
        color_min = fill_color;
        color_max = fill_color;
        const unsigned char noise = 24;
        color_min.r -= noise;
        color_min.g -= noise;
        color_min.b -= noise;
        color_max.r += noise;
        color_max.g += noise;
        color_max.b += noise;
        if (texture_type == zox_texture_dirt) {
            /*color_min.r += 16;
            color_max.r += 32;
            color_min.g += 8;
            color_max.g += 16;
            color_min.b += 8;
            color_max.b += 16;*/
        } else if (texture_type == zox_texture_grass) {
            /*greenRange.x *= 2;
            greenRange.y *= 2;
            blueRange.x = redRange.x - 30;
            blueRange.y = redRange.y - 30;
            redRange.x /= 2;
            redRange.y /= 2;*/
        } else if (texture_type == zox_texture_sand) {
            /*redRange.x = redRange.y = 206 - 50;
            greenRange.x = greenRange.y = 179 - 50;
            blueRange.x = blueRange.y = 59 - 30;
            redRange.x -= 10 + rand() % 30;
            greenRange.x -= 10 + rand() % 30;
            blueRange.x -= 10 + rand() % 20;*/
        } else if (texture_type == zox_texture_stone) {
            /*redRange.x = redRange.y = 100;
            greenRange.x = greenRange.y = 100;
            blueRange.x = blueRange.y = 100;
            redRange.x -= 10 + rand() % 20;
            greenRange.x -= 10 + rand() % 20;
            blueRange.x -= 10 + rand() % 20;*/
        } else if (zox_texture_obsidian) {
            /*redRange.x = redRange.y = 42;
            greenRange.x = greenRange.y = 42;
            blueRange.x = blueRange.y = 42;
            redRange.x -= 6 + rand() % 12;
            greenRange.x -= 6 + rand() % 12;
            blueRange.x -= 6 + rand() % 12;*/
        }
    }
    if (texture_type == zox_texture_graybox) {
        generate_texture_graybox(data, size, int2_zero, size);
        //generate_texture_graybox(textureData, textureSize, (int2) { 0, 0 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
        //generate_texture_graybox(textureData, textureSize, (int2) { textureSize->value.x / 2, 0 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
        //generate_texture_graybox(textureData, textureSize, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
        //generate_texture_graybox(textureData, textureSize, (int2) { 0, textureSize->value.y / 2 }, (int2) { textureSize->value.x / 2, textureSize->value.y / 2 });
    } else {
        for (int j = 0; j < size.x; j++) {
            for (int k = 0; k < size.y; k++) {
                int index = j + k * size.x;
                if (texture_type == zox_texture_none) {
                    int distanceToMidX = abs_integer(size.x / 2 - j);
                    int distanceToMidY = abs_integer(size.y / 2 - k);
                    if (distanceToMidX + distanceToMidY >= size.x / 2) {
                        data[index].r = 0;
                        data[index].g = 0;
                        data[index].b = 0;
                        data[index].a = 0;
                        continue;
                    }
                }
                data[index] = color_min;
                if (color_max.r != color_min.r) data[index].r += rand() % (color_max.r - color_min.r);
                if (color_max.g != color_min.g) data[index].g += rand() % (color_max.g - color_min.g);
                if (color_max.b != color_min.b) data[index].b += rand() % (color_max.b - color_min.b);
                if (color_max.a != color_min.a) data[index].a += rand() % (color_max.a - color_min.a);
                /*if (j >= textureSize->value.x / 2 && k < textureSize->value.y / 2) {
                    textureData->value[index].g *= 2;
                    textureData->value[index].b = textureData->value[index].r - 30;
                    textureData->value[index].r /= 2;
                }*/
                // textureData->value[index].a = rand() % 256;
                // debug sides of textureData, starts at top left
                if (texture_type == zox_texture_none) {
                    if (j == 0) {
                        data[index].r = 255;
                    } else if (k == 0) {
                        data[index].g = 255;
                    } else if (j == size.x - 1) {
                        data[index].b = 255;
                    } else if (k == size.y - 1) {
                        data[index].r = 255;
                        data[index].g = 255;
                    }
                }
                if (outline_type == zox_outline_type_full) {
                    // outline voxel textures
                    if (j == 0 || k == 0 || j == size.x - 1 || k == size.y - 1) {
                        data[index].r = 0;
                        data[index].g = 0;
                        data[index].b = 0;
                    }
                } else if (outline_type == zox_outline_type_half) {
                    if (j == 0 || k == 0 || j == size.x - 1 || k == size.y - 1) {
                        data[index].r /= 2;
                        data[index].g /= 2;
                        data[index].b /= 2;
                    }
                } else if (outline_type == zox_outline_type_faded) {
                    if (j == 0 || k == 0 || j == size.x - 1 || k == size.y - 1) {
                        data[index].r *= 5;
                        data[index].g *= 5;
                        data[index].b *= 5;
                        data[index].r /= 6;
                        data[index].g /= 6;
                        data[index].b /= 6;
                    }
                }
                // printf("textureData value: %i\n", textureData->value[index].r);
            }
        }
    }
}
