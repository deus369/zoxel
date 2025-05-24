float3 generate_hsv_v_s(const float2 hue_limits, const float2 value_limits, const float2 saturation_limits) {
    return (float3) {
        hue_limits.x + (hue_limits.y - hue_limits.x) * (rand() % 100) * 0.01f,
        saturation_limits.x + (saturation_limits.y - saturation_limits.x) * (rand() % 100) * 0.01f,
        value_limits.x + (value_limits.y - value_limits.x) * (rand() % 100) * 0.01f };
}