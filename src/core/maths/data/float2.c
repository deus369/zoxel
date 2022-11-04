//! A basic x2 building block.
typedef struct
{
    float x;
    float y;
} float2;

float2 float2_multiply_float(float2 input, float mul) // by-value param invokes class copy-ctor
{
    input.x *= mul;
    input.y *= mul;
    return input;
}

float2 normalize2D(float2 input)
{
    float length = sqrt(input.x * input.x + input.y * input.y);
    return (float2) { input.x / length, input.y / length };
}