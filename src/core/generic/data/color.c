//! A basic x2 building block.
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} color;

#define color_white (color) { 255, 255, 255, 255 }
#define color_black (color) { 0, 0, 0, 255 }

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
