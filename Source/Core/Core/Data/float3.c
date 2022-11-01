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

float3 float3_divide_float(float3 input, float mul) // by-value param invokes class copy-ctor
{
    input.x /= mul;
    input.y /= mul;
    input.z /= mul;
    return input;
}

float3 float3_normalize(float3 input)
{
    float length = sqrt(input.x * input.x + input.y * input.y + input.z * input.z);
    return (float3) { input.x / length, input.y / length, input.z / length };
}

float3 float3_cross(float3 a, float3 b)
{
    return (float3) { 
        a.y * b.z - a.z * b.y,
        a.y * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
     };
}