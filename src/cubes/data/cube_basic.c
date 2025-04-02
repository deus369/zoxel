// 24 unique vertices (4 per face)
const float3 cube3_vertices[] = {
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

const int cube3_indicies[] = {
    0, 1, 2, 2, 3, 0,         // Left
    4, 7, 6, 6, 5, 4,         // Right (reversed order)
    10, 11, 8, 8, 9, 10,       // Bottom (reversed order)
    14, 13, 12, 12, 15, 14,     // Top
    16, 19, 18, 18, 17, 16,     // Back (reversed order)
    20, 21, 22, 22, 23, 20      // Front
};
