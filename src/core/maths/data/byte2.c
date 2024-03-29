typedef struct {
    unsigned char x;
    unsigned char y;
} byte2;

#define byte2_zero (byte2) { 0, 0 }

byte2 byte2_multiply_int(byte2 input, int mul) {
    return (byte2) { input.x * mul, input.y * mul };
}

int byte2_array_index(byte2 input, byte2 size) {
    return input.x + input.y * size.x;
}