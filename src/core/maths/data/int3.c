//! A basic x2 building block.
#ifndef is_int3
    #define is_int3
    typedef struct
    {
        int x;
        int y;
        int z;
    } int3;
#endif

#define int3_zero (int3) { 0, 0, 0 }

unsigned char int3_equals(int3 a, int3 b) {
    if (a.x == b.x && a.y == b.y && a.z == b.z)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int3 int3_multiply_int3(int3 a, int3 b) {
    return (int3) { a.x * b.x, a.y * b.y, a.z * b.z };
}

int3 int3_add(int3 a, int3 b) {
    return (int3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

int3 int3_multiply_int(int3 a, int b) {
    return (int3) { a.x * b, a.y * b, a.z * b };
}

void int3_multiply_int_p(int3* input, int mul) {
    input->x *= mul;
    input->y *= mul;
    input->z *= mul;
}

int int3_array_index(int3 input, int3 size) {
    // return input.x + input.y * size.x + input.z * size.x * size.y;
    // return (position.z + size.z * (position.y + size.y * position.x));
    return input.z + size.z * (input.y + size.y * input.x);
}

int int3_array_index2(int3 input, int3 size) {
    return input.z + size.z * (input.y + size.y * input.x);
}

int int3_array_size(int3 size) {
    return size.x * size.y * size.z;
}

int3 int3_left(int3 input) {
    return (int3) { input.x - 1, input.y, input.z };
}

int3 int3_reverse_left(int3 input, int3 size) {
    return (int3) { size.x - 1, input.y, input.z };
}

int3 int3_right(int3 input) {
    return (int3) { input.x + 1, input.y, input.z };
}

int3 int3_reverse_right(int3 input, int3 size) {
    return (int3) { 0, input.y, input.z };
}

int3 int3_down(int3 input) {
    return (int3) { input.x, input.y - 1, input.z };
}

int3 int3_reverse_down(int3 input, int3 size) {
    return (int3) { input.x, size.y - 1, input.z };
}

int3 int3_up(int3 input) {
    return (int3) { input.x, input.y + 1, input.z };
}

int3 int3_reverse_up(int3 input, int3 size) {
    return (int3) { input.x, 0, input.z };
}

int3 int3_back(int3 input) {
    return (int3) { input.x, input.y, input.z - 1 };
}

int3 int3_reverse_back(int3 input, int3 size) {
    return (int3) { input.x, input.y, size.z - 1 };
}

int3 int3_front(int3 input) {
    return (int3) { input.x, input.y, input.z + 1 };
}

int3 int3_reverse_front(int3 input, int3 size) {
    return (int3) { input.x, input.y, 0 };
}