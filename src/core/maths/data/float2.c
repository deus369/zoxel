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

float2 float2_divide(float2 input, float div) // by-value param invokes class copy-ctor
{
    input.x /= div;
    input.y /= div;
    return input;
}

float2 get_float2_from_int2(int2 input)
{
    return (float2) { (float) input.x, (float) input.y };
}

int2 get_int2_from_float2(float2 input)
{
    return (int2) { (int) ceil(input.x), (int) ceil(input.y) };
}

float2 float2_sub(float2 a, float2 b)
{
    return (float2) { a.x - b.x, a.y - b.y };
}

float2 float2_normalize(float2 input)
{
    float length = sqrt(input.x * input.x + input.y * input.y);
    return float2_divide(input, length);
}

float2 float2_add(float2 a, float2 b)
{
    return (float2) { a.x + b.x, a.y + b.y };
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