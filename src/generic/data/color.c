#define color_null (color) { 0, 0, 0, 0}
#define color_white (color) { 255, 255, 255, 255 }
#define color_gray (color) { 125, 125, 125, 255 }
#define color_gray_dark (color) { 55, 55, 55, 255 }
#define color_black (color) { 0, 0, 0, 255 }
#define color_red (color) { 255, 0, 0, 255 }
#define color_green (color) { 0, 255, 0, 255 }
#define color_blue (color) { 0, 0, 255, 255 }
#define color_cyan (color) { 0, 255, 255, 255 }
#define color_yellow (color) { 255, 255, 0, 255 }
#define color_purple (color) { 255, 0, 255, 255 }

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
        (int) input.a / 255.0f
    };
}

static inline void color_multiply_float(color *input, const float multiplier) {
    int r = (int)(input->r * multiplier);
    int g = (int)(input->g * multiplier);
    int b = (int)(input->b * multiplier);
    input->r = (byte)(r > 255 ? 255 : (r < 0 ? 0 : r));
    input->g = (byte)(g > 255 ? 255 : (g < 0 ? 0 : g));
    input->b = (byte)(b > 255 ? 255 : (b < 0 ? 0 : b));
}

static inline color color_grayscale(byte value) {
    return (color) { value, value, value, 255 };
}

static inline color color_grayscale_a(byte v, byte a) {
    return (color) { v, v, v, a };
}

static inline color color_mutate(color c, byte m) {
    int dr = (int) c.r + (-m + rand() % (2 * m + 1));
    int dg = (int) c.g + (-m + rand() % (2 * m + 1));
    int db = (int) c.b + (-m + rand() % (2 * m + 1));
    // Clamp to [0, 255]
    c.r = (byte) (dr < 0 ? 0 : (dr > 255 ? 255 : dr));
    c.g = (byte) (dg < 0 ? 0 : (dg > 255 ? 255 : dg));
    c.b = (byte) (db < 0 ? 0 : (db > 255 ? 255 : db));
    return c;
}