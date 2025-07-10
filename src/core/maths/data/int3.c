const int3 int3_zero = (int3) { 0, 0, 0 };
const int3 int3_chaos = (int3) { -666, -666, -666 };

#define int3_left (int3) { -1, 0, 0 }
#define int3_right (int3) { 1, 0, 0 }
#define int3_down (int3) { 0, -1, 0 }
#define int3_up (int3) { 0, 1, 0 }
#define int3_backward (int3) { 0, 0, -1 }
#define int3_forward (int3) { 0, 0, 1 }
const int3 int3_directions[] = {
    int3_left,
    int3_right,
    int3_down,
    int3_up,
    int3_backward,
    int3_forward };

static inline byte int3_equals(const int3 a, const int3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

static inline int3 int3_multiply_int3(const int3 a, const int3 b) {
    return (int3) { a.x * b.x, a.y * b.y, a.z * b.z };
}

static inline int3 int3_add(const int3 a, const int3 b) {
    return (int3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

static inline int3 int3_sub(const int3 a, const int3 b) {
    return (int3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

static inline int3 int3_div(const int3 a, const int3 b) {
    return (int3) { a.x / b.x, a.y / b.y, a.z / b.z };
}

static inline void int3_add_int3(int3 *a, const int3 b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

static inline int3 int3_multiply_int(const int3 a, const int b) {
    return (int3) { a.x * b, a.y * b, a.z * b };
}

static inline void int3_multiply_int_p(int3* input, const int mul) {
    input->x *= mul;
    input->y *= mul;
    input->z *= mul;
}

static inline int int3_array_index(const int3 input, const int3 size) {
    return input.z + size.z * (input.y + size.y * input.x);
}

static inline byte int3_to_node_index(const int3 position) {
    return position.x * 4 + position.y * 2 + position.z;
}

static inline int int3_array_index2(const int3 input, const int3 size) {
    return input.z + size.z * (input.y + size.y * input.x);
}

static inline int int3_array_size(const int3 size) {
    return size.x * size.y * size.z;
}

static inline int3 int3_move_left(const int3 input) {
    return (int3) { input.x - 1, input.y, input.z };
}

static inline int3 int3_move_right(const int3 input) {
    return (int3) { input.x + 1, input.y, input.z };
}

static inline int3 int3_move_down(const int3 input) {
    return (int3) { input.x, input.y - 1, input.z };
}

static inline int3 int3_move_up(const int3 input) {
    return (int3) { input.x, input.y + 1, input.z };
}

static inline int3 int3_move_back(const int3 input) {
    return (int3) { input.x, input.y, input.z - 1 };
}

static inline int3 int3_move_front(const int3 input) {
    return (int3) { input.x, input.y, input.z + 1 };
}

static inline int3 int3_reverse_left(const int3 input, const int3 size) {
    return (int3) { size.x - 1, input.y, input.z };
}

static inline int3 int3_reverse_right(const int3 input, const int3 size) {
    return (int3) { 0, input.y, input.z };
}

static inline int3 int3_reverse_down(const int3 input, const int3 size) {
    return (int3) { input.x, size.y - 1, input.z };
}

static inline int3 int3_reverse_up(const int3 input, const int3 size) {
    return (int3) { input.x, 0, input.z };
}

static inline int3 int3_reverse_back(const int3 input, const int3 size) {
    return (int3) { input.x, input.y, size.z - 1 };
}

static inline int3 int3_reverse_front(const int3 input, const int3 size) {
    return (int3) { input.x, input.y, 0 };
}

static inline float int3_distance(const int3 a, const int3 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

static inline int int3_max(const int3 a, const int3 b) {
    return int_max(int_max(int_abs(b.x - a.x), int_abs(b.y - a.y)), int_abs(b.z - a.z));
}

static inline int int3_max_xz(const int3 a, const int3 b) {
    return int_max(int_abs(b.x - a.x), int_abs(b.z - a.z));
}

static inline byte int3_in_bounds(const int3 input, const int3 size) {
    return (input.x >= 0 && input.x < size.x && input.y >= 0 && input.y < size.y && input.z >= 0 && input.z < size.z);
}

static inline float3 int3_to_float3(const int3 input) {
    return (float3) { input.x, input.y, input.z };
}

static inline float3 byte3_to_float3(const byte3 input) {
    return (float3) { input.x, input.y, input.z };
}

// depreciated
static inline float3 float3_from_int3(const int3 input) {
    return (float3) { input.x, input.y, input.z };
}

static inline int3 int3_single(int value) {
    return (int3) { value, value, value };
}