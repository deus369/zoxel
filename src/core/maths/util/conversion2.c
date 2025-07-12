static inline byte2 int2_to_byte2(int2 input) {
    return (byte2) { input.x, input.y };
}

// used for mouse rotation
static inline float4 float2_to_rotation(float2 value) {
    float4 output = quaternion_identity;
    output.x = value.x;
    output.y = value.y;
    // quaternion_normalize(&output);
    return output;
}
