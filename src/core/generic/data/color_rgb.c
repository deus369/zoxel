typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color_rgb;

const color_rgb color_rgb_white = (color_rgb) { 255, 255, 255 };

unsigned char color_rgb_equal(color_rgb a, color_rgb b) {
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

void color_rgb_multiply_float(color_rgb *input, float multiplier) {
    input->r = (unsigned char) (input->r * multiplier);
    input->g = (unsigned char) (input->g * multiplier);
    input->b = (unsigned char) (input->b * multiplier);
}

float3 color_rgb_to_float3(color_rgb input) {
    return (float3) { input.r / 255.0f, input.g / 255.0f, input.b / 255.0f };
}

color_rgb color_rgb_from_float3(float3 input) {
    return (color_rgb) { (int) (input.x * 255.0f), (int) (input.y * 255.0f), (int) (input.z * 255.0f) };
}

zoxel_dynamic_array(color_rgb)