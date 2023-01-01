//! A basic x2 building block.
typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} color;

unsigned char color_equal(color a, color b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

float4 color_to_float4(color input)
{
    return (float4) {
        (int) input.r / 255.0f,
        (int) input.g / 255.0f,
        (int) input.b / 255.0f,
        (int) input.a / 255.0f };
}