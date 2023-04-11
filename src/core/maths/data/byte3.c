typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char z;
} byte3;

const byte3 byte3_zero = (byte3) { 0, 0, 0 };

unsigned char byte3_array_index(byte3 input, byte3 size) {
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