#define noise_values_length 512
unsigned char values[noise_values_length];
uint32_t global_seed;

int noise_fast_floor(float x) {
    return (x > 0) ? ((int)x) : (((int)x) - 1);
}

float noise_gradient(int hash, float x, float y) {
    int h = hash & 7;      // Convert low 3 bits of hash code
    float u = h < 4 ? x : y;  // into 8 simple gradient directions,
    float v = h < 4 ? y : x;  // and compute the dot product with (x,y).
    return ((h & 1) != 0 ? -u : u) + ((h & 2) != 0 ? -2.0f * v : 2.0f * v);
}

int noise_mod(int x, int m) {
    int a = x % m;
    return a < 0 ? a + m : a;
}

float generate_noise_2D(float2 point, float frequency) {
    point.x *= frequency;
    point.y *= frequency;
    const float F2 = 0.366025403f; // F2 = 0.5*(sqrt(3.0)-1.0)
    const float G2 = 0.211324865f; // G2 = (3.0-Math.sqrt(3.0))/6.0
    float n0, n1, n2; // Noise contributions from the three corners
    // Skew the input space to determine which simplex cell we're in
    int s = (point.x + point.y) * F2; // Hairy factor for 2D
    int xs = point.x + s;
    int ys = point.y + s;
    int i = noise_fast_floor(xs);
    int j = noise_fast_floor(ys);
    float t = (i + j) * G2;
    float X0 = i - t; // Unskew the cell origin back to (x,y) space
    float Y0 = j - t;
    float x0 = point.x - X0; // The x,y distances from the cell origin
    float y0 = point.y - Y0;
    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
    if (x0 > y0) {
        i1 = 1;
        j1 = 0;
    } else {
        // lower triangle, XY order: (0,0)->(1,0)->(1,1)
        i1 = 0;
        j1 = 1;
    }
    // upper triangle, YX order: (0,0)->(0,1)->(1,1)
    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6
    float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
    float y1 = y0 - j1 + G2;
    float x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
    float y2 = y0 - 1.0f + 2.0f * G2;
    // Wrap the integer indices at 256, to avoid indexing perm[] out of bounds
    int ii = noise_mod(i, 256);
    int jj = noise_mod(j, 256);
    // Calculate the contribution from the three corners
    float t0 = 0.5f - x0 * x0 - y0 * y0;
    if (t0 < 0.0f) {
        n0 = 0.0f;
    } else {
        t0 *= t0;
        n0 = t0 * t0 * noise_gradient(values[ii + values[jj]], x0, y0);
    }
    float t1 = 0.5f - x1 * x1 - y1 * y1;
    if (t1 < 0.0f) {
        n1 = 0.0f;
    } else {
        t1 *= t1;
        n1 = t1 * t1 * noise_gradient(values[ii + i1 + values[jj + j1]], x1, y1);
    }
    float t2 = 0.5f - x2 * x2 - y2 * y2;
    if (t2 < 0.0f) {
        n2 = 0.0f;
    } else {
        t2 *= t2;
        n2 = t2 * t2 * noise_gradient(values[ii + 1 + values[jj + 1]], x2, y2);
    }
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    float result = 40.0f * (n0 + n1 + n2);
    result = 0.5f * ( 1.0f + result ); // rescale result between 0 and 1
    return result;
}


void set_noise_seed(uint32_t seed) {
    if (global_seed == seed) return;
    global_seed = seed;
    // zox_log(" + seed set [%" PRIu32 "]\n", global_seed)
    srand(seed);
    for (int i = 0; i < noise_values_length; i++) {
        values[i] = (unsigned char) rand() % 256; // (byte) random.NextInt(0, 255);
    }
    // testing
    // float value = generate_noise_2D(float2_zero, 0.01f);
    // zox_log(" > realm seed [%i]\n", value)
}
