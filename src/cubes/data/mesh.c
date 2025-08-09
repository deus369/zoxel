static const int cube_indicies_length = 36;
static const int cube_indicies[] = {
    0, 2, 6, 6, 4, 0,   // Left
    7, 3, 1, 1, 5, 7,   // Right
    0, 4, 5, 5, 1, 0,   // Bottom
    7, 6, 2, 2, 3, 7,   // Top
    4, 6, 7, 7, 5, 4,   // Back
    3, 2, 0, 0, 1, 3    // Front
};

// centred cube verts
static const int cube_vertices_length = 8;
static const float3 cube_vertices[] = {
    { -default_cube_size, -default_cube_size,  default_cube_size },   //0
    { default_cube_size, -default_cube_size,  default_cube_size },    //1
    { -default_cube_size,  default_cube_size,  default_cube_size },   //2
    { default_cube_size,  default_cube_size,  default_cube_size },    //3
    { -default_cube_size, -default_cube_size, -default_cube_size },   //4
    { default_cube_size, -default_cube_size, -default_cube_size },    //5
    { -default_cube_size,  default_cube_size, -default_cube_size },   //6
    { default_cube_size,  default_cube_size, -default_cube_size }     //7
};

static const int cube_uvs_length = 8;
static const float2 cube_uvs[] = {
    { 0, 0 },   //0
    { 0, 1 },   //1
    { 1, 0 },   //2
    { 1, 1 },   //3
    { 0, 0 },   //4
    { 0, 1 },   //5
    { 1, 0 },   //6
    { 1, 1 },   //7
};

static const int cube_vertices_f_length = 8 * 3;
static const float cube_vertices_f[] = {
    -default_cube_size, -default_cube_size, -default_cube_size,    // 0
    -default_cube_size,  default_cube_size, -default_cube_size,    // 1
    default_cube_size,  default_cube_size, -default_cube_size,    // 2
    default_cube_size, -default_cube_size, -default_cube_size,    // 3
    -default_cube_size, -default_cube_size, default_cube_size,     // 4
    -default_cube_size,  default_cube_size, default_cube_size,     // 5
    default_cube_size,  default_cube_size, default_cube_size,     // 6
    default_cube_size, -default_cube_size, default_cube_size      // 7
};

// skybox, inverted
static const float cube_vertices_inverted[] = {
    -default_cube_size, -default_cube_size,  default_cube_size,   //0
    default_cube_size, -default_cube_size,  default_cube_size,    //1
    -default_cube_size,  default_cube_size,  default_cube_size,   //2
    default_cube_size,  default_cube_size,  default_cube_size,    //3
    -default_cube_size, -default_cube_size, -default_cube_size,   //4
    default_cube_size, -default_cube_size, -default_cube_size,    //5
    -default_cube_size,  default_cube_size, -default_cube_size,   //6
    default_cube_size,  default_cube_size, -default_cube_size     //7
};
static const color_rgb cube_colors[] = {
    { 255, 255, 255 },   //0
    { 255, 255, 255 },   //1
    { 255, 255, 255 },   //2
    { 255, 255, 255 },   //3
    { 255, 255, 255 },   //4
    { 255, 255, 255 },   //5
    { 255, 255, 255 },   //6
    { 255, 255, 255 }    //7
};
static const int cube_indicies_inverted[] = {
    6, 2, 0, 0, 4, 6,   // Left
    1, 3, 7, 7, 5, 1,   // Right
    5, 4, 0, 0, 1, 5,   // Bottom
    2, 6, 7, 7, 3, 2,   // Top
    7, 6, 4, 4, 5, 7,   // Back
    0, 2, 3, 3, 1, 0    // Front
};