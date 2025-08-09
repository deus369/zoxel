static const int cube2_indicies_length = 36;
static const int cube2_indicies[] = {
    0, 1, 2, 2, 3, 0,         // Left
    4, 7, 6, 6, 5, 4,         // Right (reversed order)
    8, 11, 10, 10, 9, 8,       // Bottom (reversed order)
    12, 13, 14, 14, 15, 12,     // Top
    16, 19, 18, 18, 17, 16,     // Back (reversed order)
    20, 21, 22, 22, 23, 20      // Front
};

// 24 unique vertices (4 per face)
static const int cube2_vertices_length = 24;
static const float3 cube2_vertices[] = {
    // Left
    {-default_cube_size, -default_cube_size,  default_cube_size },
    {-default_cube_size,  default_cube_size,  default_cube_size },
    {-default_cube_size,  default_cube_size, -default_cube_size },
    {-default_cube_size, -default_cube_size, -default_cube_size },

    // Right
    { default_cube_size, -default_cube_size,  default_cube_size },
    { default_cube_size,  default_cube_size,  default_cube_size },
    { default_cube_size,  default_cube_size, -default_cube_size },
    { default_cube_size, -default_cube_size, -default_cube_size },

    // Bottom
    {-default_cube_size, -default_cube_size, -default_cube_size },
    {-default_cube_size, -default_cube_size,  default_cube_size },
    { default_cube_size, -default_cube_size,  default_cube_size },
    { default_cube_size, -default_cube_size, -default_cube_size },

    // Top
    {-default_cube_size,  default_cube_size, -default_cube_size },
    {-default_cube_size,  default_cube_size,  default_cube_size },
    { default_cube_size,  default_cube_size,  default_cube_size },
    { default_cube_size,  default_cube_size, -default_cube_size },

    // Back
    {-default_cube_size, -default_cube_size, -default_cube_size },
    { default_cube_size, -default_cube_size, -default_cube_size },
    { default_cube_size,  default_cube_size, -default_cube_size },
    {-default_cube_size,  default_cube_size, -default_cube_size },

    // Front
    {-default_cube_size, -default_cube_size,  default_cube_size },
    { default_cube_size, -default_cube_size,  default_cube_size },
    { default_cube_size,  default_cube_size,  default_cube_size },
    {-default_cube_size,  default_cube_size,  default_cube_size }
};

// 24 UV coordinates
static const int cube2_uvs_length = 24;
static const float2 cube2_uvs[] = {
    {0, 0}, {1, 0}, {1, 1}, {0, 1}, // Left
    {0, 0}, {1, 0}, {1, 1}, {0, 1}, // Right
    {0, 0}, {1, 0}, {1, 1}, {0, 1}, // Bottom
    {0, 0}, {1, 0}, {1, 1}, {0, 1}, // Top
    {0, 0}, {1, 0}, {1, 1}, {0, 1}, // Back
    {0, 0}, {1, 0}, {1, 1}, {0, 1}  // Front
};