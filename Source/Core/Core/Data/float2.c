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