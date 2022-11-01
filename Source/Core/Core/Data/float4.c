//! A basic x2 building block.
typedef struct
{
    float x;
    float y;
    float z;
    float w;
} float4;

void print_float4(const float4 input)
{
    printf("Float4 [%f %f %f %f]\n", input.x, input.y, input.z, input.w);
}

//! Also called Conjugation in maths.
float4 float4_reverse(float4 input)
{ 
    return (float4) { -input.x, -input.y, -input.z, -input.w };
}