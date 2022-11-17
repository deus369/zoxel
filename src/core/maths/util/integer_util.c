// baasic abs for int
int abs_integer(int value)
{
    if (value < 0)
    {
        return -value;
    }
    else
    {
        return value;
    }
}


int integer_min(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

float3 float3_from_int3(int3 input)
{
    return (float3) { input.x, input.y, input.z };
}