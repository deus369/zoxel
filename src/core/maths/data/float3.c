//! A basic x2 building block.
typedef struct {
    float x;
    float y;
    float z;
} float3;

void float3_print(const float3 input) {
    zoxel_log("    Float3 [%f %f %f]\n", input.x, input.y, input.z);
}

void float3_make_zero(float3* value) {
    value->x = 0;
    value->y = 0;
    value->z = 0;
}

float3 float3_multiply_float(const float3 input, const float mul) {
    return (float3) { input.x * mul, input.y * mul, input.z * mul };
}

float3 float3_add(const float3 inputA, const float3 inputB) {
    return (float3) { inputA.x + inputB.x, inputA.y + inputB.y, inputA.z + inputB.z };
}

float3 float3_subtract_float3(const float3 inputA, const float3 inputB) {
    return (float3) { inputA.x - inputB.x, inputA.y - inputB.y, inputA.z - inputB.z };
}

float float3_distance(const float3 a, const float3 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

void float3_multiply_float_p(float3* input, const float mul) {
    input->x *= mul;
    input->y *= mul;
    input->z *= mul;
}

void float3_divide_float_p(float3* input, const float div) {
    input->x /= div;
    input->y /= div;
    input->z /= div;
}

void float3_add_float3_p(float3* a, const float3 b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

void float3_subtract_float3_p(float3* a, const float3 b) {
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
}

float3 float3_divide_float(const float3 input, const float div) {
    return (float3) { input.x / div, input.y / div, input.z / div };
}

float3 float3_normalize(const float3 input) {
    float length = sqrt(input.x * input.x + input.y * input.y + input.z * input.z);
    if (float_abs(length) <= 0.00001f) return input;
    return float3_divide_float(input, length);
}

//! Fixed from https://www.mathsisfun.com/algebra/vectors-cross-product.html
float3 float3_cross(const float3 a, const float3 b) {
    return (float3) { 
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

float float3_dot(const float3 a, const float3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float float3_length(const float3 v) {
    return sqrt(float3_dot(v, v));
}

float3 float3_from_byte3(const byte3 input) {
    return (float3) { input.x, input.y, input.z };
}

#define float3_zero (float3) { 0, 0, 0 }
#define float3_backward (float3) { 0, 0, -1 }
#define float3_forward (float3) { 0, 0, 1 }
#define float3_left (float3) { -1, 0, 0 }
#define float3_right (float3) { 1, 0, 0 }
#define float3_down (float3) { 0, -1, 0 }
#define float3_up (float3) { 0, 1, 0 }

const float3 octree_positions_float3s[] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 1.0f },
    { 1.0f, 0.0f, 0.0f },
    { 1.0f, 0.0f, 1.0f },
    { 1.0f, 1.0f, 0.0f },
    { 1.0f, 1.0f, 1.0f }
};
