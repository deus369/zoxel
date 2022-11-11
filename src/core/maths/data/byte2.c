//! A basic x2 building block using bytes.
typedef struct
{
    unsigned char x;
    unsigned char y;
} byte2;


byte2 byte2_multiply_int(byte2 input, int mul)
{
    return (byte2) { input.x * mul, input.y * mul };
}