float3 int3_to_float3(const int3 input) {
    return (float3) { input.x, input.y, input.z };
}

// depreciated
float3 float3_from_int3(const int3 input) {
    return (float3) { input.x, input.y, input.z };
}
