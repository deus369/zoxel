typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char z;
} byte3;

const byte3 byte3_zero = (byte3) { 0, 0, 0 };

// 255 * 255 > 255
int byte3_array_index(byte3 input, byte3 size) {
    return input.z + size.z * (input.y + size.y * input.x);
}

unsigned char byte3_octree_array_index(byte3 input) {
    return input.z + 2 * (input.y + 2 * input.x);
}

const byte3 octree_node_size4 = (byte3) { 2, 2, 2 };

void byte3_modulus_byte(byte3 *value, unsigned char moduli) {
    value->x %= moduli;
    value->y %= moduli;
    value->z %= moduli;
}

int3 int3_from_byte3(byte3 input) {
    return (int3) { input.x, input.y, input.z };
}

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

byte3 byte3_left(byte3 input) {
    return (byte3) { input.x - 1, input.y, input.z };
}

byte3 byte3_right(byte3 input) {
    return (byte3) { input.x + 1, input.y, input.z };
}

byte3 byte3_down(byte3 input) {
    return (byte3) { input.x, input.y - 1, input.z };
}

byte3 byte3_up(byte3 input) {
    return (byte3) { input.x, input.y + 1, input.z };
}

byte3 byte3_back(byte3 input) {
    return (byte3) { input.x, input.y, input.z - 1 };
}

byte3 byte3_front(byte3 input) {
    return (byte3) { input.x, input.y, input.z + 1 };
}

byte3 byte3_reverse_left(byte3 input, byte3 size) {
    return (byte3) { size.x - 1, input.y, input.z };
}

byte3 byte3_reverse_right(byte3 input, byte3 size) {
    return (byte3) { 0, input.y, input.z };
}

byte3 byte3_reverse_down(byte3 input, byte3 size) {
    return (byte3) { input.x, size.y - 1, input.z };
}

byte3 byte3_reverse_up(byte3 input, byte3 size) {
    return (byte3) { input.x, 0, input.z };
}

byte3 byte3_reverse_back(byte3 input, byte3 size) {
    return (byte3) { input.x, input.y, size.z - 1 };
}

byte3 byte3_reverse_front(byte3 input, byte3 size) {
    return (byte3) { input.x, input.y, 0 };
}