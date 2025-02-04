zoxel_dynamic_array(color_rgb)

#define color_rgb_white (color_rgb) { 255, 255, 255 }
// const color_rgb color_rgb_white = (color_rgb) { 255, 255, 255 };

byte color_rgb_equal(const color_rgb a, const color_rgb b) {
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

void color_rgb_multiply_float(color_rgb *input, const float multiplier) {
    input->r = (byte) (input->r * multiplier);
    input->g = (byte) (input->g * multiplier);
    input->b = (byte) (input->b * multiplier);
}
