static inline int3 byte3_to_int3(byte3 input) {
    return (int3) { input.x, input.y, input.z };
}

static inline byte3 int3_to_byte3(int3 input) {
    return (byte3) { input.x, input.y, input.z };
}

static inline float2 int2_to_float2(int2 input) {
    return (float2) { (float) input.x, (float) input.y };
}

static inline int2 float2_to_int2(float2 input) {
    return (int2) { (int) ceil(input.x), (int) ceil(input.y) };
}

static inline int2 byte2_to_int2(byte2 input) {
    return (int2) { (int) input.x, (int) input.y };
}

static inline float2 byte2_to_float2(byte2 v) {
    return (float2) { v.x / 255.0f, v.y / 255.0f };
}

static inline float3 float3_from_byte3(const byte3 input) {
    return (float3) { input.x, input.y, input.z };
}

static inline int3 float3_to_int3(const float3 input) {
    return (int3) { (int) input.x, (int) input.y, (int) input.z };
}