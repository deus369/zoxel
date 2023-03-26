//! A basic x2 building block.
typedef struct {
    float x;
    float y;
    float z;
} float3;

#define float3_zero (float3) { 0, 0, 0 }

void float3_print(const float3 input) {
    zoxel_log("    Float3 [%f %f %f]\n", input.x, input.y, input.z);
}

float3 float3_multiply_float(float3 input, float mul) {
    input.x *= mul;
    input.y *= mul;
    input.z *= mul;
    return input;
}

float3 float3_add(float3 inputA, float3 inputB) {
    return (float3) { inputA.x + inputB.x, inputA.y + inputB.y, inputA.z + inputB.z };
}

void float3_multiply_float_p(float3* input, float mul) {
    input->x *= mul;
    input->y *= mul;
    input->z *= mul;
}

void float3_add_float3_p(float3* a, float3 b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

float3 float3_divide_float(float3 input, float div) {
    return (float3) { input.x / div, input.y / div, input.z / div };
}

float3 float3_normalize(float3 input) {
    float length = sqrt(input.x * input.x + input.y * input.y + input.z * input.z);
    return float3_divide_float(input, length);
}

//! Fixed from https://www.mathsisfun.com/algebra/vectors-cross-product.html
float3 float3_cross(float3 a, float3 b) {
    return (float3) { 
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

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