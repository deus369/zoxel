byte byte3_equals(const byte3 a, const byte3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

int byte3_array_index(const byte3 input, const byte3 size) {
    return input.z + size.z * (input.y + size.y * input.x);
}

byte byte3_octree_array_index(const byte3 input) {
    return input.z + 2 * (input.y + 2 * input.x);
}

byte3 byte3_add(const byte3 a, const byte3 b) {
    return (byte3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

void byte3_add_byte3_p(byte3 *value, const byte3 add) {
    value->x += add.x;
    value->y += add.y;
    value->z += add.z;
}

void byte3_modulus_byte(byte3 *value, const byte moduli) {
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

const byte3 byte3_full = (byte3) { 255, 255, 255 };

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

byte byte3_in_bounds(const byte3 input, const byte3 size) {
    return (input.x >= 0 && input.x < size.x && input.y >= 0 && input.y < size.y && input.z >= 0 && input.z < size.z);
}

byte byte3_on_edge(const byte3 pos, const byte3 size) {
    return pos.x == 0 || pos.y == 0 || pos.z == 0 || pos.x == size.x - 1 || pos.y == size.y - 1 || pos.z == size.z - 1;
}

byte byte3_on_edge_xz(const byte3 pos, const byte3 size) {
    return pos.x == 0 || pos.z == 0 || pos.x == size.x - 1 || pos.z == size.z - 1;
}

byte byte3_on_edges(const byte3 pos, const byte3 size) {
    byte edges_count = 0;
    if (pos.x == 0 || pos.x == size.x - 1) edges_count++;
    if (pos.y == 0 || pos.y == size.y - 1) edges_count++;
    if (pos.z == 0 || pos.z == size.z - 1) edges_count++;
    return edges_count >= 2;
}

void byte3_multiply_byte(byte3* input, const byte mul) {
    input->x *= mul;
    input->y *= mul;
    input->z *= mul;
}
