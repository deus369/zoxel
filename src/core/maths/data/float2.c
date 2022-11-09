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

float float2_highest(float2 input)
{
    if (input.x > input.y)
    {
        return input.x;
    }
    else
    {
        return input.y;
    }
}

float float2_lowest(float2 input)
{
    if (input.x < input.y)
    {
        return input.x;
    }
    else
    {
        return input.y;
    }
}

float2 normalize2D(float2 input)
{
    float length = sqrt(input.x * input.x + input.y * input.y);
    return (float2) { input.x / length, input.y / length };
}

float2 float2_add_float2(float2 a, float2 b)
{
    return (float2) { a.x + b.x, a.y + b.y };
}