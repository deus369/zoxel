//! A basic x2 building block.
typedef struct
{
    int x;
    int y;
    int z;
} int3;

int int3_array_index(int3 input, int3 size)
{
    // return input.x + input.y * size.x + input.z * size.x * size.y;
    // return (position.z + size.z * (position.y + size.y * position.x));
    return input.z + size.z * (input.y + size.y * input.x);
}

int3 int3_left(int3 input)
{
    return (int3) { input.x - 1, input.y, input.z };
}

int3 int3_right(int3 input)
{
    return (int3) { input.x + 1, input.y, input.z };
}

int3 int3_down(int3 input)
{
    return (int3) { input.x, input.y - 1, input.z };
}

int3 int3_up(int3 input)
{
    return (int3) { input.x, input.y + 1, input.z };
}

int3 int3_back(int3 input)
{
    return (int3) { input.x, input.y, input.z - 1 };
}

int3 int3_front(int3 input)
{
    return (int3) { input.x, input.y, input.z + 1 };
}

int3 int3_multiply_int3(int3 a, int3 b)
{
    return (int3) { a.x * b.x, a.y * b.y, a.z * b.z };
}

int3 int3_add_int3(int3 a, int3 b)
{
    return (int3) { a.x + b.x, a.y + b.y, a.z + b.z };
}
