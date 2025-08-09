static inline byte byte3_equals(const byte3 a, const byte3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

static inline byte3 byte3_single(const byte a) {
    return (byte3) { a, a, a };
}

static inline int byte3_array_index(const byte3 input, const byte3 size) {
    return input.z + size.z * (input.y + size.y * input.x);
}

static inline int byte3_array_indexl(const byte3 input, const byte length) {
    return input.z + length * (input.y + length * input.x);
}

static inline byte byte3_octree_array_index(const byte3 input) {
    return input.z + 2 * (input.y + 2 * input.x);
}

static inline byte3 byte3_add(const byte3 a, const byte3 b) {
    return (byte3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

static inline void byte3_add_byte3_p(byte3 *value, const byte3 add) {
    value->x += add.x;
    value->y += add.y;
    value->z += add.z;
}

static inline void byte3_modulus_byte(byte3 *value, const byte moduli) {
    value->x %= moduli;
    value->y %= moduli;
    value->z %= moduli;
}

static inline byte3 byte3_left(const byte3 input) {
    return (byte3) { input.x - 1, input.y, input.z };
}

static inline byte3 byte3_right(const byte3 input) {
    return (byte3) { input.x + 1, input.y, input.z };
}

static inline byte3 byte3_down(const byte3 input) {
    return (byte3) { input.x, input.y - 1, input.z };
}

static inline byte3 byte3_up(const byte3 input) {
    return (byte3) { input.x, input.y + 1, input.z };
}

static inline byte3 byte3_back(const byte3 input) {
    return (byte3) { input.x, input.y, input.z - 1 };
}

static inline byte3 byte3_front(const byte3 input) {
    return (byte3) { input.x, input.y, input.z + 1 };
}

static inline byte3 byte3_reverse_left(const byte3 input, const byte3 size) {
    return (byte3) { size.x - 1, input.y, input.z };
}

static inline byte3 byte3_reverse_right(const byte3 input) {
    return (byte3) { 0, input.y, input.z };
}

static inline byte3 byte3_reverse_down(const byte3 input, const byte3 size) {
    return (byte3) { input.x, size.y - 1, input.z };
}

static inline byte3 byte3_reverse_up(const byte3 input) {
    return (byte3) { input.x, 0, input.z };
}

static inline byte3 byte3_reverse_back(const byte3 input, const byte3 size) {
    return (byte3) { input.x, input.y, size.z - 1 };
}

static inline byte3 byte3_reverse_front(const byte3 input) {
    return (byte3) { input.x, input.y, 0 };
}

static inline byte byte3_in_bounds(const byte3 input, const byte3 size) {
    return (input.x < size.x && input.y < size.y && input.z < size.z);
}

static inline byte byte3_on_edge(const byte3 pos, const byte3 size) {
    return pos.x == 0 || pos.y == 0 || pos.z == 0 || pos.x == size.x - 1 || pos.y == size.y - 1 || pos.z == size.z - 1;
}

static inline byte byte3_on_edge_xz(const byte3 pos, const byte3 size) {
    return pos.x == 0 || pos.z == 0 || pos.x == size.x - 1 || pos.z == size.z - 1;
}

static inline byte byte3_on_edges(const byte3 pos, const byte3 size) {
    byte edges_count = 0;
    if (pos.x == 0 || pos.x == size.x - 1) edges_count++;
    if (pos.y == 0 || pos.y == size.y - 1) edges_count++;
    if (pos.z == 0 || pos.z == size.z - 1) edges_count++;
    return edges_count >= 2;
}

static inline void byte3_multiply_byte(byte3* input, const byte mul) {
    input->x *= mul;
    input->y *= mul;
    input->z *= mul;
}