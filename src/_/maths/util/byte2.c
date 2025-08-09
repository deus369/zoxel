static inline byte2 byte2_multiply_int(const byte2 input, const int mul) {
    return (byte2) { input.x * mul, input.y * mul };
}

static inline int byte2_array_index(const byte2 input, const byte2 size) {
    return input.x + input.y * size.x;
}


static inline byte byte2_on_edge(const byte2 pos, const byte2 size) {
    return pos.x == 0 || pos.y == 0 || pos.x == size.x - 1 || pos.y == size.y - 1;
}

static inline byte2 byte2_single(const byte a) {
    return (byte2) { a, a };
}