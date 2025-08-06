zoxel_dynamic_array(color_rgb)

#define color_rgb_white (color_rgb) { 255, 255, 255 }
#define color_rgb_gray (color_rgb) { 152, 152, 152 }
#define color_rgb_black (color_rgb) { 0, 0, 0 }
#define color_rgb_red (color_rgb) { 255, 0, 0 }
#define color_rgb_green (color_rgb) { 0, 255, 0 }
#define color_rgb_blue (color_rgb) { 0, 0, 255 }
#define color_rgb_cyan (color_rgb) { 0, 255, 255 }
#define color_rgb_yellow (color_rgb) { 255, 255, 0 }
#define color_rgb_purple (color_rgb) { 255, 0, 255 }

static inline byte color_rgb_equal(const color_rgb a, const color_rgb b) {
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

static inline void color_rgb_multiply_float(color_rgb *input, const float multiplier) {
    int r = (int)(input->r * multiplier);
    int g = (int)(input->g * multiplier);
    int b = (int)(input->b * multiplier);
    input->r = (byte)(r > 255 ? 255 : (r < 0 ? 0 : r));
    input->g = (byte)(g > 255 ? 255 : (g < 0 ? 0 : g));
    input->b = (byte)(b > 255 ? 255 : (b < 0 ? 0 : b));
}

static inline color_rgb color_rgb_grayscale(byte v) {
    return (color_rgb) { v, v, v };
}