const int3 int3_zero = (int3) { 0, 0, 0 };
// #define int3_zero (int3) { 0, 0, 0 }
const int3 int3_chaos = (int3) { -666, -666, -666 };

#define int3_left (int3) { -1, 0, 0 }
#define int3_right (int3) { 1, 0, 0 }
#define int3_down (int3) { 0, -1, 0 }
#define int3_up (int3) { 0, 1, 0 }
#define int3_backward (int3) { 0, 0, -1 }
#define int3_forward (int3) { 0, 0, 1 }
const int3 int3_directions[] = { int3_left, int3_right, int3_down, int3_up, int3_backward, int3_forward };

byte int3_equals(const int3 a, const int3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

int3 int3_multiply_int3(const int3 a, const int3 b) {
    return (int3) { a.x * b.x, a.y * b.y, a.z * b.z };
}

int3 int3_add(const int3 a, const int3 b) {
    return (int3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

int3 int3_sub(const int3 a, const int3 b) {
    return (int3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

int3 int3_div(const int3 a, const int3 b) {
    return (int3) { a.x / b.x, a.y / b.y, a.z / b.z };
}

void int3_add_int3(int3 *a, const int3 b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

int3 int3_multiply_int(const int3 a, const int b) {
    return (int3) { a.x * b, a.y * b, a.z * b };
}

void int3_multiply_int_p(int3* input, const int mul) {
    input->x *= mul;
    input->y *= mul;
    input->z *= mul;
}

int int3_array_index(const int3 input, const int3 size) {
    // return input.x + input.y * size.x + input.z * size.x * size.y;
    // return (position.z + size.z * (position.y + size.y * position.x));
    return input.z + size.z * (input.y + size.y * input.x);
}

byte int3_to_node_index(const int3 position) {
    return position.x * 4 + position.y * 2 + position.z;
}

int int3_array_index2(const int3 input, const int3 size) {
    return input.z + size.z * (input.y + size.y * input.x);
}

int int3_array_size(const int3 size) {
    return size.x * size.y * size.z;
}

int3 int3_move_left(const int3 input) {
    return (int3) { input.x - 1, input.y, input.z };
}

int3 int3_move_right(const int3 input) {
    return (int3) { input.x + 1, input.y, input.z };
}

int3 int3_move_down(const int3 input) {
    return (int3) { input.x, input.y - 1, input.z };
}

int3 int3_move_up(const int3 input) {
    return (int3) { input.x, input.y + 1, input.z };
}

int3 int3_move_back(const int3 input) {
    return (int3) { input.x, input.y, input.z - 1 };
}

int3 int3_move_front(const int3 input) {
    return (int3) { input.x, input.y, input.z + 1 };
}

int3 int3_reverse_left(const int3 input, const int3 size) {
    return (int3) { size.x - 1, input.y, input.z };
}

int3 int3_reverse_right(const int3 input, const int3 size) {
    return (int3) { 0, input.y, input.z };
}

int3 int3_reverse_down(const int3 input, const int3 size) {
    return (int3) { input.x, size.y - 1, input.z };
}

int3 int3_reverse_up(const int3 input, const int3 size) {
    return (int3) { input.x, 0, input.z };
}

int3 int3_reverse_back(const int3 input, const int3 size) {
    return (int3) { input.x, input.y, size.z - 1 };
}

int3 int3_reverse_front(const int3 input, const int3 size) {
    return (int3) { input.x, input.y, 0 };
}

float int3_distance(const int3 a, const int3 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

int int3_max(const int3 a, const int3 b) {
    return int_max(int_max(int_abs(b.x - a.x), int_abs(b.y - a.y)), int_abs(b.z - a.z));
}

int int3_max_xz(const int3 a, const int3 b) {
    return int_max(int_abs(b.x - a.x), int_abs(b.z - a.z));
}

byte int3_in_bounds(const int3 input, const int3 size) {
    return (input.x >= 0 && input.x < size.x && input.y >= 0 && input.y < size.y && input.z >= 0 && input.z < size.z);
}


float3 int3_to_float3(const int3 input) {
    return (float3) { input.x, input.y, input.z };
}

float3 byte3_to_float3(const byte3 input) {
    return (float3) { input.x, input.y, input.z };
}

// depreciated
float3 float3_from_int3(const int3 input) {
    return (float3) { input.x, input.y, input.z };
}

int3 find_closest_point(const int3* points, const int points_length, const int3 target) {
    if (points == NULL) {
        return int3_zero;
    }
    if (points_length == 0) {
        return int3_zero;
    }
    if (points_length == 1) {
        return points[0];
    }
    int3 closest_point = points[0];
    float closest_distance = int3_distance(points[0], target); // 1000000;
    for (byte i = 1; i < points_length; i++) {
        const float distance = int3_distance(points[i], target);
        if (distance < closest_distance) {
            closest_distance = distance;
            closest_point = points[i];
        }
    }
    return closest_point;
}
