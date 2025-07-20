// fog
byte is_render_fog = 1;
float fog_density = 0.03f; // 0326f;

static inline float get_fog_density() {
    return is_render_fog ? fog_density * fog_density : 0;
}

static inline float4 get_fog_value() {
    return float4_from_float3(color_rgb_to_float3(fog_color), get_fog_density());
}