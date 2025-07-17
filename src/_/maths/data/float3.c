#define float3_zero (float3) { 0, 0, 0 }
#define float3_half (float3) { 0.5f, 0.5f, 0.5f }
#define float3_one (float3) { 1, 1, 1 }
#define float3_left (float3) { -1, 0, 0 }
#define float3_right (float3) { 1, 0, 0 }
#define float3_down (float3) { 0, -1, 0 }
#define float3_up (float3) { 0, 1, 0 }
#define float3_backward (float3) { 0, 0, -1 }
#define float3_forward (float3) { 0, 0, 1 }

static inline byte float3_equals(const float3 a, const float3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

static inline void float3_print(const float3 input) {
    zox_log("    Float3 [%f %f %f]\n", input.x, input.y, input.z);
}

static inline void float3_flip(float3* value) {
    value->x *= -1;
    value->y *= -1;
    value->z *= -1;
}

static inline void float3_make_zero(float3* value) {
    value->x = 0;
    value->y = 0;
    value->z = 0;
}

static inline float3 float3_halve(const float3 input) {
    return (float3) { input.x * 0.5f, input.y * 0.5f, input.z * 0.5f };
}

static inline float3 float3_single(const float input) {
    return (float3) { input, input, input };
}

static inline float3 float3_multiply_float(const float3 input, const float mul) {
    return (float3) { input.x * mul, input.y * mul, input.z * mul };
}

static inline float3 float3_add(const float3 inputA, const float3 inputB) {
    return (float3) { inputA.x + inputB.x, inputA.y + inputB.y, inputA.z + inputB.z };
}

static inline float3 float3_sub(const float3 inputA, const float3 inputB) {
    return (float3) { inputA.x - inputB.x, inputA.y - inputB.y, inputA.z - inputB.z };
}

static inline float3 float3_mul(const float3 a, const float3 b) {
    return (float3) { a.x * b.x, a.y * b.y, a.z * b.z };
}

// depreciated!
static inline float3 float3_multiply_float3(const float3 a, const float3 b) {
    return (float3) { a.x * b.x, a.y * b.y, a.z * b.z };
}

static inline float3 float3_subtract_float3(const float3 inputA, const float3 inputB) {
    return (float3) { inputA.x - inputB.x, inputA.y - inputB.y, inputA.z - inputB.z };
}

static inline float3 float3_mid(const float3 a, const float3 b) {
    return (float3) { a.x + (b.x - a.x) * 0.5f, a.y + (b.y - a.y) * 0.5f, a.z + (b.z - a.z) * 0.5f };
}

static inline float float3_distance(const float3 a, const float3 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

static inline void float3_multiply_float_p(float3* input, const float mul) {
    input->x *= mul;
    input->y *= mul;
    input->z *= mul;
}

static inline void float3_divide_float_p(float3* input, const float div) {
    input->x /= div;
    input->y /= div;
    input->z /= div;
}

static inline void float3_add_float3_p(float3* a, const float3 b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

static inline void float3_subtract_float3_p(float3* a, const float3 b) {
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
}

static inline void float3_multiply_float3_p(float3* a, const float3 b) {
    a->x *= b.x;
    a->y *= b.y;
    a->z *= b.z;
}

static inline float3 float3_divide_float(const float3 input, const float div) {
    return (float3) { input.x / div, input.y / div, input.z / div };
}

static inline float3 float3_abs(const float3 input) {
    return (float3) { float_abs(input.x), float_abs(input.y), float_abs(input.z) };
}

static inline float3 float3_normalize(const float3 input) {
    float length = sqrt(input.x * input.x + input.y * input.y + input.z * input.z);
    if (float_abs(length) <= 0.00001f) {
        return input;
    } else {
        return float3_divide_float(input, length);
    }
}

//! Fixed from https://www.mathsisfun.com/algebra/vectors-cross-product.html
static inline float3 float3_cross(const float3 a, const float3 b) {
    return (float3) { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}

static inline float float3_dot(const float3 a, const float3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline float float3_length(const float3 v) {
    return sqrt(float3_dot(v, v));
}

static inline float float3_magnitude(const float3 value) {
    return sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
}

static inline float3 float3_sign(const float3 value) {
    return (float3) { float_sign(value.x), float_sign(value.y), float_sign(value.z) };
}

static inline float3 float3_lerp(const float3 a, const float3 b, const float t) {
    return (float3) { a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z) };
}

static inline float float3_sign2(const float3 value) {
    float abs_x = float_abs(value.x);
    float abs_y = float_abs(value.y);
    float abs_z = float_abs(value.z);
    if (abs_x >= abs_y && abs_x >= abs_z) {
        return (value.x < 0) ? -1.0f : ((value.x > 0) ? 1.0f : 0.0f);
    } else if (abs_y >= abs_x && abs_y >= abs_z) {
        return (value.y < 0) ? -1.0f : ((value.y > 0) ? 1.0f : 0.0f);
    } else {
        return (value.z < 0) ? -1.0f : ((value.z > 0) ? 1.0f : 0.0f);
    }
}