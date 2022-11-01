//! A basic x2 building block.
typedef struct
{
    float x;
    float y;
    float z;
} float3;

float3 float3_multiply_float(float3 input, float mul) // by-value param invokes class copy-ctor
{
    input.x *= mul;
    input.y *= mul;
    input.z *= mul;
    return input;
}