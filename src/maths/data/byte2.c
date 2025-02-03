#define byte2_zero (byte2) { 0, 0 }

byte2 byte2_multiply_int(const byte2 input, const int mul) {
    return (byte2) { input.x * mul, input.y * mul };
}

int byte2_array_index(const byte2 input, const byte2 size) {
    return input.x + input.y * size.x;
}
