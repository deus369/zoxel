#define color_null (color) { 0, 0, 0, 0}
#define color_white (color) { 255, 255, 255, 255 }
#define color_gray (color) { 125, 125, 125, 255 }
#define color_gray_dark (color) { 55, 55, 55, 255 }
#define color_black (color) { 0, 0, 0, 255 }
#define color_red (color) { 255, 0, 0, 255 }
#define color_green (color) { 0, 255, 0, 255 }
#define color_blue (color) { 0, 0, 255, 255 }

static inline byte color_equal(const color a, const color b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

static inline byte is_color_null(const color a) {
    return color_equal(a, color_null);
}

static inline float4 color_to_float4(const color input) {
    return (float4) {
        (int) input.r / 255.0f,
        (int) input.g / 255.0f,
        (int) input.b / 255.0f,
        (int) input.a / 255.0f };
}

static inline void color_multiply_float(color *input, const float multiplier) {
    input->r = (byte) (input->r * multiplier);
    input->g = (byte) (input->g * multiplier);
    input->b = (byte) (input->b * multiplier);
}

static inline color color_grayscale(byte value) {
    return (color) { value, value, value, 255 };
}