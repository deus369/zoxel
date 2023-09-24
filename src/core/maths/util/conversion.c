int3 byte3_to_int3(byte3 input) {
    return (int3) { input.x, input.y, input.z };
}

byte3 int3_to_byte3(int3 input) {
    return (byte3) { input.x, input.y, input.z };
}

float2 int2_to_float2(int2 input) {
    return (float2) { (float) input.x, (float) input.y };
}

int2 float2_to_int2(float2 input) {
    return (int2) { (int) ceil(input.x), (int) ceil(input.y) };
}

int2 byte2_to_int2(byte2 input) {
    return (int2) { (int) input.x, (int) input.y };
}