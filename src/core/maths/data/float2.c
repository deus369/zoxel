//! A basic x2 building block.
typedef struct {
    float x;
    float y;
} float2;

#define float2_zero (float2) { 0.0f, 0.0f }
#define float2_half (float2) { 0.5f, 0.5f }
#define float2_top_left (float2) { 0, 1 }

float2 float2_multiply_float(float2 input, float mul) {
    input.x *= mul;
    input.y *= mul;
    return input;
}

void float2_multiply_float_p(float2 *input, float mul) {
    input->x *= mul;
    input->y *= mul;
}

void float2_multiply_float2_p(float2 *input, const float2 mul) {
    input->x *= mul.x;
    input->y *= mul.y;
}

void float2_divide_float2(float2 *input, const float2 div) {
    input->x /= div.x;
    input->y /= div.y;
}

float2 float2_divide(float2 input, float div) {
    input.x /= div;
    input.y /= div;
    return input;
}

void float2_divide_p(float2 *input, float div) {
    input->x /= div;
    input->y /= div;
}

void float2_add_float2_p(float2 *input, const float2 add) {
    input->x += add.x;
    input->y += add.y;
}

float2 float2_sub(float2 a, float2 b) {
    return (float2) { a.x - b.x, a.y - b.y };
}

void float2_normalize_p(float2 *input) {
    float length = sqrt(input->x * input->x + input->y * input->y);
    float2_divide_p(input, length);
}

float2 float2_normalize(float2 input) {
    float length = sqrt(input.x * input.x + input.y * input.y);
    return float2_divide(input, length);
}

float2 float2_add(float2 a, float2 b) {
    return (float2) { a.x + b.x, a.y + b.y };
}

float2 float2_subtract(float2 a, float2 b) {
    return (float2) { a.x - b.x, a.y - b.y };
}

float float2_highest(float2 input) {
    if (input.x > input.y) return input.x;
    else return input.y;
}

float float2_lowest(float2 input) {
    if (input.x < input.y) return input.x;
    else return input.y;
}

float2 normalize2D(float2 input) {
    float length = sqrt(input.x * input.x + input.y * input.y);
    return (float2) { input.x / length, input.y / length };
}
