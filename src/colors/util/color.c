static inline float3 color_to_float3(const color input) {
    return (float3) { input.r / 255.0f, input.g / 255.0f, input.b / 255.0f };
}

static inline color color_from_float3(const float3 input, const float alpha) {
    return (color) { (int) (input.x * 255.0f), (int) (input.y * 255.0f), (int) (input.z * 255.0f), (int) (alpha * 255.0f) };
}

static inline color float4_to_color(const float4 input) {
    return (color) { (int) (input.x * 255.0f), (int) (input.y * 255.0f), (int) (input.z * 255.0f), (int) (input.w * 255.0f) };
}

static inline color_rgb color_to_color_rgb(const color input) {
    return (color_rgb) { input.r, input.g, input.b };
}