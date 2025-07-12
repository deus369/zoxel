static inline float3 color_rgb_to_float3(const color_rgb input) {
    return (float3) { input.r / 255.0f, input.g / 255.0f, input.b / 255.0f };
}

static inline color_rgb color_rgb_from_float3(const float3 input) {
    return (color_rgb) { (int) (input.x * 255.0f), (int) (input.y * 255.0f), (int) (input.z * 255.0f) };
}

static inline color color_rgb_to_color(const color_rgb input) {
    return (color) { input.r, input.g, input.b, 255 };
}