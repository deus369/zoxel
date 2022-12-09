//! A basic x2 building block.
typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} color;

bool color_equal(color a, color b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}