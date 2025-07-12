const uint safety_checks_drawline = 1000;

int2 font_point_to_pixel(const byte2 point, const int2 size, const float2 pad) {
    float2 pointf = byte2_to_float2(point);
    pointf.x = pad.x + (1.0f - pad.x * 2) * pointf.x;
    pointf.y = pad.y + (1.0f - pad.y * 2) * pointf.y;
    return (int2) {
        (int) (pointf.x * size.x),
        (int) (pointf.y * size.y),
    };
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

void generate_splotches_lines(color* data, const int2 size, const FontData *fontData, const color line_color, const byte splotch_size, const float2 padding) {
    if (splotch_size == 0) {
        return;
    }
    for (int i = 0; i < fontData->length; i += 2) {
        int2 pointA = font_point_to_pixel(fontData->value[i], size, padding);
        int2 pointB = font_point_to_pixel(fontData->value[i + 1], size, padding);
        /*int2 pointA = byte2_to_int2(fontData->value[i]);
        int2 pointB = byte2_to_int2(fontData->value[i + 1]);
        // scale points to texture size
        pointA.x = (int) ((pointA.x / 255.0f) * size.x);
        pointA.y = (int) ((pointA.y / 255.0f) * size.y);
        pointB.x = (int) ((pointB.x / 255.0f) * size.x);
        pointB.y = (int) ((pointB.y / 255.0f) * size.y);*/
        int distance = int2_distance(pointA, pointB);
        float2 direction = float2_normalize(float2_sub(int2_to_float2(pointB), int2_to_float2(pointA)));
        #ifdef debug_font_texture
        zox_log("Font Data %i %ix%i > %ix%i\n", i, pointA.x, pointA.y, pointB.x, pointB.y)
        zox_log("    - %ix%i > %ix%i\n", pointA.x, pointA.y, pointB.x, pointB.y);
        zox_log("    - distance %i direction %fx%f\n", distance, direction.x, direction.y);
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

void generate_font_lines(color* data, const int2 size, const FontData *fontData, const color line_color, const float2 padding) {
    // point A to B - use FontData byte2 data.
    for (int i = 0; i < fontData->length; i += 2) {
        int2 pointA = font_point_to_pixel(fontData->value[i], size, padding);
        int2 pointB = font_point_to_pixel(fontData->value[i + 1], size, padding);
        draw_texture_line(data, size, pointA, pointB, line_color);
#ifdef debug_font_texture
        zox_log("-> fonting: %i %ix%i > %ix%i", i, pointA.x, pointA.y, pointB.x, pointB.y);
#endif
    }
}