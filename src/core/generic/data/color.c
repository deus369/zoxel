//! A basic x2 building block.
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} color;

unsigned char color_equal(const color a, const color b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

float4 color_to_float4(const color input) {
    return (float4) {
        (int) input.r / 255.0f,
        (int) input.g / 255.0f,
        (int) input.b / 255.0f,
        (int) input.a / 255.0f };
}

void color_multiply_float(color *input, const float multiplier) {
    input->r = (unsigned char) (input->r * multiplier);
    input->g = (unsigned char) (input->g * multiplier);
    input->b = (unsigned char) (input->b * multiplier);
}

float3 color_to_float3(const color input) {
    return (float3) { input.r / 255.0f, input.g / 255.0f, input.b / 255.0f };
}

color color_from_float3(const float3 input, const float alpha) {
    return (color) { (int) (input.x * 255.0f), (int) (input.y * 255.0f), (int) (input.z * 255.0f), (int) (alpha * 255.0f) };
}

color color_from_float4(const float4 input) {
    return (color) { (int) (input.x * 255.0f), (int) (input.y * 255.0f), (int) (input.z * 255.0f), (int) (input.w * 255.0f) };
}
