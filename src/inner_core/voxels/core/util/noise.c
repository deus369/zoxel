const float sqrtofthree = 1.73205080757f;   // sqrt(3.0f)
const float trianglesToSquares = (sqrtofthree - 1.0f) / 2.0f;
const float squaresToTriangles = (3.0f - sqrtofthree) / 6.0f;

int int_floor(float input)
{
    return (int) floor(input);
}

float simplex_fun_int_1D(float3 point, int ix)
{
    float x = point.x - ix;
    float f = 1.0f - x * x;
    float f2 = f * f;
    float f3 = f * f2;
    return f3;
}

float simplex_fun_1D(float3 point, float frequency)
{
    point = float3_multiply_float(point, frequency);
    int ix = int_floor(point.x);
    float sample = simplex_fun_int_1D(point, ix);
    sample += simplex_fun_int_1D(point, ix + 1);
    return sample * 2.0f - 1.0f;
}

float simplex_fun_int_2D(float3 point, int ix, int iy)
{
    float unskew = (ix + iy) * squaresToTriangles;
    float x = point.x - ix + unskew;
    float y = point.z - iy + unskew;
    float f = 0.5f - x * x - y * y;
    if (f > 0.0f)
    {
        float f2 = f * f;
        float f3 = f * f2;
        return f3;
    }
    return 0.0f;
}

float simplex_fun_2D(float3 point, float frequency)
{
    point = float3_multiply_float(point, frequency);
    float skew = (point.x + point.z) * trianglesToSquares;
    float sx = point.x + skew;
    float sy = point.z + skew;
    int ix = int_floor(sx);
    int iy = int_floor(sy);
    float sample = simplex_fun_int_2D(point, ix, iy);
    sample += simplex_fun_int_2D(point, ix + 1, iy + 1);
    if (sx - ix >= sy - iy)
    {
        sample += simplex_fun_int_2D(point, ix + 1, iy);
    }
    else {
        sample += simplex_fun_int_2D(point, ix, iy + 1);
    }
    // return sample * 2.0f - 1.0f;
    return sample * (8.0f * 2.0f) - 1.0f;
}