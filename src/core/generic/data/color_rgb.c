typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color_rgb;

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