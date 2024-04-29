typedef struct {
    float x;
    float y;
    float z;
    float w;
} float4;

#define float4_zero (float4) { 0, 0, 0, 0 }
#define float4_identity (float4) { 0, 0, 0, 1 }

void print_float4(const float4 input) {
    zoxel_log("    Float4 [%f %f %f %f]\n", input.x, input.y, input.z, input.w);
}

float4 float4_multiply_float(const float4 input, const float mul) {
    return (float4) { input.x * mul, input.y * mul, input.z * mul, input.w * mul };
}

float4 float4_multiply_divide(const float4 input, const float div) {
    return (float4) { input.x / div, input.y / div, input.z / div, input.w / div };
}

float float4_dot(const float4 a, const float4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float float4_length(const float4 v) {
    return sqrt(float4_dot(v, v));
}

float4 float4_normalize(const float4 q) {
    float length = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    return float4_multiply_divide(q, length);
}

void quaternion_rotate_quaternion_p(float4 *output, const float4 q2) {
    float4 q1 = *output;
    output->w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    output->x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    output->y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    output->z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
}

float4 quaternion_rotate(const float4 q1, const float4 q2) {
    float4 output;
    output.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    output.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    output.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    output.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    return output;
}

//! Also called Conjugation in maths. Apparently x needs to be position still?
// confirmed here https://www.youtube.com/watch?v=A6A0rpV9ElA
float4 float4_inverse(const float4 input) {
    // return (float4) { input.x, -input.y, -input.z, -input.w };
    return (float4) { -input.x, -input.y, -input.z, input.w };
}

float4 quaternion_inverse(const float4 q) {
    float sqr = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    return float4_multiply_divide(q, sqr);
}

float4 float3_to_float4(const float3 input) {
    return (float4) { input.x, input.y, input.z, 0 };
}

float3 float4_xyz(const float4 input) {
    return (float3) { input.x, input.y, input.z };
}

// This output is wrong - [0, 0.7, 0, 0.7] (rotate left)
/**
 * t = 2 * cross(q.xyz, v)
 * v' = v + q.w * t + cross(q.xyz, t)
*/
float3 float4_rotate_float3(const float4 rotation, const float3 value) {
    /*float4 value4 = float3_to_float4(value3);
    float4 conjRotation = quaternion_inverse(rotation);
    return float4_xyz(quaternion_rotate(rotation, quaternion_rotate(value4, conjRotation)));*/
    float3 rotationXYZ = float4_xyz(rotation);
    float3 t = float3_multiply_float(float3_cross(rotationXYZ, value), 2.0f);
    float3 crossB = float3_cross(rotationXYZ, t);
    float3 scaledT = float3_multiply_float(t, rotation.w);
    return float3_add(value, float3_add(scaledT, crossB));
}

void float4_rotate_float3_p(const float4 rotation, float3 *value) {
    float3 rotationXYZ = float4_xyz(rotation);
    float3 t = float3_multiply_float(float3_cross(rotationXYZ, (float3) { value->x, value->y, value->z }), 2.0f);
    float3 crossB = float3_cross(rotationXYZ, t);
    float3 scaledT = float3_multiply_float(t, rotation.w);
    float3_add_float3_p(value, float3_add(scaledT, crossB));
}

void float4_multiply_float_p(float4* input, const float mul) {
    input->x *= mul;
    input->y *= mul;
    input->z *= mul;
    input->w *= mul;
}
