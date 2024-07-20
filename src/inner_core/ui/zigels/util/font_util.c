// #define zox_debug_font_textures
const uint safety_checks_floodfill = 4000;
const uint safety_checks_drawline = 1000;
const unsigned char is_splotches = 1;
// const unsigned char splotch_size = 2;
#ifdef zox_debug_font_textures
    const color nothing_font_color = { 125, 100, 100, 255 };
#else
    const color nothing_font_color = { 0, 0, 0, 0 };
#endif

void flood_fill_texture(color* data, const int2 size, const color air_color, const color boundary_color, const color fill_color, const int x, const int y) {
    int index = int2_array_index((int2) { x, y }, size);
    if (!color_equal(data[index], air_color)) return;
    int visited[size.x * size.y];
    memset(visited, 0, sizeof(visited));
    int stack[size.x * size.y * 2 * 4];
    int stack_top = 0;
    stack[stack_top++] = x; // x-coordinate
    stack[stack_top++] = y; // y-coordinate
    // Loop until the stack is empty
    uint checks = 0;
    while (stack_top > 0 && checks < safety_checks_floodfill) {
        // Pop the top pixel from the stack
        int y = stack[--stack_top];
        int x = stack[--stack_top];
        // Check if the pixel is within the texture bounds and hasn't been visited
        index = int2_array_index((int2) { x, y }, size);
        if (x >= 0 && x < size.x && y >= 0 && y < size.y && !visited[index]) {
            visited[index] = 1;
            if (color_equal(data[index], boundary_color) ||color_equal(data[index], fill_color)) continue;
            data[index] = fill_color;
            // zox_log("filling [%ix%i]\n", x, y)
            // Push neighboring pixels onto the stack (left, right, up, down)
            stack[stack_top++] = x - 1; // left
            stack[stack_top++] = y;
            stack[stack_top++] = x + 1; // right
            stack[stack_top++] = y;
            stack[stack_top++] = x;     // up
            stack[stack_top++] = y - 1;
            stack[stack_top++] = x;     // down
            stack[stack_top++] = y + 1;
        }
        checks++;
    }
}

// raycast from all 4 sides!
void scanline_fill_texture(color* data, const int2 size, const color air_color, const color boundary_color, const color fill_color) {
    for (int y = 0; y < size.y; y++) {
        unsigned char intersects = 0;
        for (int x = 0; x < size.x; x++) {
            const int index = int2_array_index((int2) { x, y }, size);
            if (intersects) {
                flood_fill_texture(data, size, air_color, boundary_color, fill_color, x, y);
                break;
            } else if (color_equal(data[index], boundary_color)) {
                intersects++;
            }
        }
        intersects = 0;
        for (int x = size.x - 1; x >= 0; x--) {
            const int index = int2_array_index((int2) { x, y }, size);
            if (intersects) {
                flood_fill_texture(data, size, air_color, boundary_color, fill_color, x, y);
                break;
            } else if (color_equal(data[index], boundary_color)) {
                intersects++;
            }
        }
    }
    for (int x = 0; x < size.x; x++) {
        unsigned char intersects = 0;
        intersects = 0;
        for (int y = 0; y < size.y; y++) {
            const int index = int2_array_index((int2) { x, y }, size);
            if (intersects) {
                flood_fill_texture(data, size, air_color, boundary_color, fill_color, x, y);
                break;
            } else if (color_equal(data[index], boundary_color)) {
                intersects++;
            }
        }
        intersects = 0;
        for (int y = size.y - 1; y >= 0; y--) {
            const int index = int2_array_index((int2) { x, y }, size);
            if (intersects) {
                flood_fill_texture(data, size, air_color, boundary_color, fill_color, x, y);
                break;
            } else if (color_equal(data[index], boundary_color)) {
                intersects++;
            }
        }
    }
}

void draw_texture_line(color* data, const int2 size, const int2 point_a, const int2 point_b, const color line_color) {
    // Calculate the texture coordinates for point_a and point_b
    int x0 = (int) point_a.x;
    int y0 = (int) point_a.y;
    int x1 = (int) point_b.x;
    int y1 = (int) point_b.y;
    // Calculate the difference between the x and y coordinates
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    // Calculate the direction of the line along the x and y axes
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    // Calculate the error terms
    int err = dx - dy;
    int e2;
    // Loop through each pixel along the line segment
    uint checks = 0;
    while (1 && checks < safety_checks_drawline) {
        // Calculate the index of the current pixel in the texture data array
        int index = (y0 * size.x + x0);
        // Set the RGBA values of the current pixel to white (255, 255, 255, 255)
        data[index] = line_color;
        // Check if we've reached the end of the line segment
        if (x0 == x1 && y0 == y1) break;
        // Calculate the next pixel coordinates
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; } // Adjust the x-coordinate
        if (e2 < dx) { err += dx; y0 += sy; } // Adjust the y-coordinate
        checks++;
    }
}

void generate_splotches_lines(color* data, const int2 size, const FontData *fontData, const color line_color, const unsigned char splotch_size) {
    if (splotch_size == 0) return;
    for (int i = 0; i < fontData->length; i += 2) {
        int2 pointA = byte2_to_int2(fontData->value[i]);
        int2 pointB = byte2_to_int2(fontData->value[i + 1]);
#ifdef debug_font_texture
        zox_log("Font Data %i %ix%i > %ix%i\n", i, pointA.x, pointA.y, pointB.x, pointB.y)
#endif
        // scale points to texture size
        pointA.x = (int) ((pointA.x / 255.0f) * size.x);
        pointA.y = (int) ((pointA.y / 255.0f) * size.y);
        pointB.x = (int) ((pointB.x / 255.0f) * size.x);
        pointB.y = (int) ((pointB.y / 255.0f) * size.y);
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
            int pointSize2 = splotch_size - 1; // rand() % splotch_size; // math.floor(random.NextFloat(pointSize.x, pointSize.y));
            // get surrounding pixels
            for (int k = -pointSize2; k <= pointSize2; k++) {
                for (int l = -pointSize2; l <= pointSize2; l++) {
                    const int2 drawPoint = (int2) { splash_point.x + k, splash_point.y + l};
                    if (drawPoint.x >= 0 && drawPoint.x < size.x && drawPoint.y >= 0 && drawPoint.y < size.y) {
                        const int array_index = int2_array_index(drawPoint, size);
                        if (color_equal(data[array_index], nothing_font_color)) data[array_index] = line_color;
                    }
                }
            }
            j += int_clamp(pointSize2, 0, pointSize2 - 1); // (int) math.clamp(pointSize2, 0, pointSize2 - 1);
        }
    }
}

void clear_texture(color* data, const int2 size) {
    int index = 0;
    for (int k = 0; k < size.y; k++) {
        for (int j = 0; j < size.x; j++) {
            data[index] = nothing_font_color;
            index++;
        }
    }
}

void generate_font_lines(color* data, const int2 size, const FontData *fontData, const color line_color) {
    // point A to B - use FontData byte2 data.
    for (int i = 0; i < fontData->length; i += 2) {
        int2 pointA = byte2_to_int2(fontData->value[i]);
        int2 pointB = byte2_to_int2(fontData->value[i + 1]);
#ifdef debug_font_texture
        zoxel_log("Font Data %i %ix%i > %ix%i\n", i, pointA.x, pointA.y, pointB.x, pointB.y);
#endif
        // scale points to texture size
        pointA.x = (int) ((pointA.x / 255.0f) * size.x);
        pointA.y = (int) ((pointA.y / 255.0f) * size.y);
        pointB.x = (int) ((pointB.x / 255.0f) * size.x);
        pointB.y = (int) ((pointB.y / 255.0f) * size.y);
        draw_texture_line(data, size, pointA, pointB, line_color);
    }
}

void generate_font_texture(color* data, const int2 size, const FontData *font_data, const color line_color,  const color fill_color, const unsigned char is_shapes,  unsigned char font_thickness) {
    // const color nothing = { 0, 0, 0, 0 };
    clear_texture(data, size);
    if (!font_data->length) return;
    if (is_shapes) {
        generate_font_lines(data, size, font_data, line_color);
        scanline_fill_texture(data, size, nothing_font_color, line_color, fill_color);
    } else {
        font_thickness++;
    }
    generate_splotches_lines(data, size, font_data, line_color, font_thickness);
}

/*
const unsigned char is_background = 0;
const int frame_thickness = size.x / 4;
const int2 redRange = { 15, 244 };
const int2 greenRange = { 15, 122 };
const int2 blueRange = { 15, 122 };
const int2 alphaRange = { 144, 256 };
const int2 alphaRange2 = { 222, 256 };
// color font_color = (color) { 5 + rand() % 120, 100 + rand() % 120, 100 + rand() % 120, 255 };
// (color) { 55, 185, 125, 255 };
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

if (!is_background) {
    textureData->value[index] = nothing;
} else if (j <= frame_thickness || k <= frame_thickness || j >= size.x - 1 - frame_thickness || k >= size.y - 1 - frame_thickness) {
    textureData->value[index] = base;
} else {
    textureData->value[index] = darker;
}*/
