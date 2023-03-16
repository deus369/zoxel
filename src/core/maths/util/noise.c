// simplex noise from catlike https://catlikecoding.com/unity/tutorials/simplex-noise/
const float sqrtofthree = 1.73205080757f;   // sqrt(3.0f)
const float trianglesToSquares = (sqrtofthree - 1.0f) / 2.0f;
const float squaresToTriangles = (3.0f - sqrtofthree) / 6.0f;

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

float simplex_fun_int_2D(float2 point, int ix, int iy)
{
    float unskew = (ix + iy) * squaresToTriangles;
    float x = point.x - ix + unskew;
    float y = point.y - iy + unskew;
    float f = 0.5f - x * x - y * y;
    if (f > 0.0f)
    {
        return f * f * f;
    }
    return 0.0f;
}

float simplex_fun_2D(float2 point, float frequency)
{
    point = float2_multiply_float(point, frequency);
    float skew = (point.x + point.y) * trianglesToSquares;
    float sx = point.x + skew;
    float sy = point.y + skew;
    int ix = int_floor(sx);
    int iy = int_floor(sy);
    float sample = simplex_fun_int_2D(point, ix, iy);
    sample += simplex_fun_int_2D(point, ix + 1, iy + 1);
    if (sx - ix >= sy - iy)
    {
        sample += simplex_fun_int_2D(point, ix + 1, iy);
    }
    else
    {
        sample += simplex_fun_int_2D(point, ix, iy + 1);
    }
    // return sample * 2.0f - 1.0f;
    return sample * (8.0f * 2.0f) - 1.0f;
}

// Returns the largest integer value less than or equal to a given value
double double_floor(double x) {
    return (int)x;
}

// Returns a smooth interpolation value between 0 and 1
double smoothstep(double t) {
    return t * t * (3 - 2 * t);
}

// Returns the dot product of two 2D vectors
double dot_product(uint32_t h, double x, double y) {
    // Convert the random integer value to a unit vector using the gradient lookup table
    static const double gradients[8][2] = {
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };
    int index = h & 7;
    double dx = gradients[index][0];
    double dy = gradients[index][1];

    // Return the dot product of the unit vector and the weights
    return dx * x + dy * y;
}

// Returns an interpolated value between a and b using the weight t
double lerp(double a, double b, double t) {
    return (1 - t) * a + t * b;
}

uint32_t hash(uint32_t x, uint32_t y, uint32_t seed) {
    uint32_t hash = seed;
    hash ^= hash << 13;
    hash ^= hash >> 7;
    hash ^= hash << 17;
    hash ^= y;
    hash ^= hash << 5;
    hash ^= hash >> 2;
    hash ^= hash << 3;
    hash ^= x;
    return hash;
}

double perlin_noise(double x, double y, double f, uint32_t seed) {
    // Hash function that maps a 2D vector to a random integer value

    // Calculate the lattice coordinates of the grid cell that contains the point (x, y)
    int x0 = (int)double_floor(x * f);
    int y0 = (int)double_floor(y * f);

    // Calculate the weights of each corner of the grid cell
    double sx = x * f - x0;
    double sy = y * f - y0;

    // Calculate the dot product of the weights and the gradients at each corner of the grid cell
    double n0 = dot_product(hash(x0, y0, seed), sx, sy);
    double n1 = dot_product(hash(x0 + 1, y0, seed), sx - 1, sy);
    double n2 = dot_product(hash(x0, y0 + 1, seed), sx, sy - 1);
    double n3 = dot_product(hash(x0 + 1, y0 + 1, seed), sx - 1, sy - 1);

    // Interpolate between the dot products using a smoothstep function
    double u = smoothstep(sx);
    double v = smoothstep(sy);

    // Interpolate between the values at the corners of the grid cell and return the result
    double noise = lerp(lerp(n0, n1, u), lerp(n2, n3, u), v);

    // Scale the noise value to the range [0, 1]
    return noise; //  (noise + 1.0) / 2.0;
}

double perlin_terrain(double x, double y, double f, uint32_t seed, int octaves)
{
    double terrain = 0.0;
    double amplitude = 1.0;
    // Add multiple scales of Perlin noise
    for (int i = 0; i < octaves; i++)
    {
        double frequency = pow(2.0, i);
        terrain += perlin_noise(x * frequency, y * frequency, f, seed) * amplitude;
        amplitude /= 2.0;
    }
    // terrain /= 4.0;
    // terrain /= (double) octaves;
    /*if (terrain > 1.0)
    {
        // printf("Terrain too high %d\n", terrain);
        terrain = 1.0;
    }*/
    return terrain;
}

        // uint32_t hash = rand();
        /*uint32_t hash = x;
        hash ^= hash << 13;
        hash ^= hash >> 7;
        hash ^= hash << 17;
        hash ^= y;
        hash ^= hash << 5;
        hash ^= hash >> 2;
        hash ^= hash << 3;
        return hash;*/