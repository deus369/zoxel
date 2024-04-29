typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char z;
} byte3;

unsigned char byte3_equals(const byte3 a, const byte3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

int byte3_array_index(const byte3 input, const byte3 size) {
    return input.z + size.z * (input.y + size.y * input.x);
}

unsigned char byte3_octree_array_index(const byte3 input) {
    return input.z + 2 * (input.y + 2 * input.x);
}

void byte3_add_byte3_p(byte3 *value, const byte3 add) {
    value->x += add.x;
    value->y += add.y;
    value->z += add.z;
}

void byte3_modulus_byte(byte3 *value, const unsigned char moduli) {
    value->x %= moduli;
    value->y %= moduli;
    value->z %= moduli;
}

byte3 byte3_left(const byte3 input) {
    return (byte3) { input.x - 1, input.y, input.z };
}

byte3 byte3_right(const byte3 input) {
    return (byte3) { input.x + 1, input.y, input.z };
}

byte3 byte3_down(const byte3 input) {
    return (byte3) { input.x, input.y - 1, input.z };
}

byte3 byte3_up(const byte3 input) {
    return (byte3) { input.x, input.y + 1, input.z };
}

byte3 byte3_back(const byte3 input) {
    return (byte3) { input.x, input.y, input.z - 1 };
}

byte3 byte3_front(const byte3 input) {
    return (byte3) { input.x, input.y, input.z + 1 };
}

byte3 byte3_reverse_left(const byte3 input, const byte3 size) {
    return (byte3) { size.x - 1, input.y, input.z };
}

byte3 byte3_reverse_right(const byte3 input, const byte3 size) {
    return (byte3) { 0, input.y, input.z };
}

byte3 byte3_reverse_down(const byte3 input, const byte3 size) {
    return (byte3) { input.x, size.y - 1, input.z };
}

byte3 byte3_reverse_up(const byte3 input, const byte3 size) {
    return (byte3) { input.x, 0, input.z };
}

byte3 byte3_reverse_back(const byte3 input, const byte3 size) {
    return (byte3) { input.x, input.y, size.z - 1 };
}

byte3 byte3_reverse_front(const byte3 input, const byte3 size) {
    return (byte3) { input.x, input.y, 0 };
}

const byte3 byte3_zero = (byte3) { 0, 0, 0 };

const byte3 octree_node_size4 = (byte3) { 2, 2, 2 };

const byte3 octree_positions_b[] = {
    { 0, 0, 0},
    { 0, 0, 1},
    { 0, 1, 0},
    { 0, 1, 1},
    { 1, 0, 0},
    { 1, 0, 1},
    { 1, 1, 0},
    { 1, 1, 1}
};
