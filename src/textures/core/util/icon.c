void generate_texture_icon(color *data, const int length, const int2 size, const color fill_color, const color outline_color, const byte frame_thickness, const byte radius, const byte is_noise) {
    int index = 0;
    const byte is_odd = radius % 2 != 0;
    int2 mid_position = int2_half(size);
    int2 pixel_position = { 0, 0 };
    for (pixel_position.y = 0; pixel_position.y < size.y; pixel_position.y++) {
        for (pixel_position.x = 0; pixel_position.x < size.x; pixel_position.x++) {
            // even numbers fix for radius
            int2 check_position = pixel_position;
            if (is_odd) {
                if (check_position.x <= radius) {
                    check_position.x += 1;
                }
                if (check_position.y <= radius) {
                    check_position.y += 1;
                }
            }
            const int distance_to_mid = int2_distance(check_position, mid_position);
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