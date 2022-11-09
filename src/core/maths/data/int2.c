//! A basic x2 building block.
typedef struct
{
    int x;
    int y;
} int2;

int2 int2_multiply_float(int2 input, float mult)
{
    return (int2) { (int) ((float) input.x * mult), (int) ((float) input.y * mult) };
}