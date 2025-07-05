void texture_swap_colors(color* data, const int2 size, const color old_color, const color new_color) {
    for (int i = 0; i < size.x * size.y; i++) {
        if (color_equal(data[i], old_color)) {
            data[i] = new_color;
        }
    }
}

// raycast from all 4 sides!
void scanline_fill_texture(color* data, const int2 size, const color air_color, const color boundary_color, const color fill_color) {
    int2 last_boundary_pixel = int2_zero;
    for (int y = 0; y < size.y; y++) {
        byte intersects = 0;
        byte found_filling = 0;
        for (int x = 0; x < size.x; x++) {
            const int index = int2_array_index((int2) { x, y }, size);
            if (color_equal(data[index], boundary_color)) {
                if (intersects && found_filling) {
                    if (!texture_does_flood_reach_edge(data, size, air_color, boundary_color, last_boundary_pixel.x, last_boundary_pixel.y)) {
                        flood_fill_texture(data, size, air_color, boundary_color, fill_color, last_boundary_pixel.x, last_boundary_pixel.y);
                    }
                }
                found_filling = 0;
                intersects = !intersects;
                if (!intersects) {
                    break;
                }
            } else {
                // find position in air
                if (!found_filling) {
                    found_filling = 1;
                    last_boundary_pixel = (int2) { x, y };
                }
            }
        }
        /*intersects = 0;
        for (int x = size.x - 1; x >= 0; x--) {
            const int index = int2_array_index((int2) { x, y }, size);
            if (intersects) {
                flood_fill_texture(data, size, air_color, boundary_color, fill_color, x, y);
                break;
            } else if (color_equal(data[index], boundary_color)) {
                intersects++;
            }
        }*/
    }
    /*for (int x = 0; x < size.x; x++) {
        byte intersects = 0;
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
    }*/
    texture_swap_colors(data, size, boundary_color, fill_color);
}