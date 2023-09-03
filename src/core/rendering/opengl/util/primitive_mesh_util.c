// mesh data
#define default_cube_size 0.5f

const int cubeIndicies3[] = {
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4
};

// createt cube floats
const float cubeVertices3[] = {
    -default_cube_size, -default_cube_size, -default_cube_size,    // 0
    -default_cube_size,  default_cube_size, -default_cube_size,    // 1
     default_cube_size,  default_cube_size, -default_cube_size,    // 2
     default_cube_size, -default_cube_size, -default_cube_size,    // 3
    -default_cube_size, -default_cube_size, default_cube_size,     // 4
    -default_cube_size,  default_cube_size, default_cube_size,     // 5
     default_cube_size,  default_cube_size, default_cube_size,     // 6
     default_cube_size, -default_cube_size, default_cube_size      // 7
};

const float3 cube_vertices[] = {
    (float3) { -default_cube_size, -default_cube_size,  default_cube_size },   //0
    (float3) { default_cube_size, -default_cube_size,  default_cube_size },    //1
    (float3) { -default_cube_size,  default_cube_size,  default_cube_size },   //2
    (float3) { default_cube_size,  default_cube_size,  default_cube_size },    //3
    (float3) { -default_cube_size, -default_cube_size, -default_cube_size },   //4
    (float3) { default_cube_size, -default_cube_size, -default_cube_size },    //5
    (float3) { -default_cube_size,  default_cube_size, -default_cube_size },   //6
    (float3) { default_cube_size,  default_cube_size, -default_cube_size }     //7
};

const float2 cube_uvs[] = {
    (float2) { 0, 0 },   //0
    (float2) { 0, 1 },   //1
    (float2) { 1, 1 },   //2
    (float2) { 1, 0 },   //3
    (float2) { 0, 0 },   //4
    (float2) { 0, 1 },   //5
    (float2) { 1, 1 },   //6
    (float2) { 1, 0 }    //7
};

const color_rgb cube_colors[] = {
    (color_rgb) { 255, 255, 255 },   //0
    (color_rgb) { 255, 255, 255 },   //1
    (color_rgb) { 255, 255, 255 },   //2
    (color_rgb) { 255, 255, 255 },   //3
    (color_rgb) { 255, 255, 255 },   //4
    (color_rgb) { 255, 255, 255 },   //5
    (color_rgb) { 255, 255, 255 },   //6
    (color_rgb) { 255, 255, 255 }    //7
};

const int cube_indicies[] = {
    // Left
    0, 2, 6,
    6, 4, 0,
    // Right
    7, 3, 1,
    1, 5, 7,
    // Bottom
    0, 4, 5,
    5, 1, 0,
    // Top
    7, 6, 2,
    2, 3, 7,
    // Back
    4, 6, 7,
    7, 5, 4,
    // Front
    3, 2, 0,
    0, 1, 3
};

// inverted
const int cube_indicies_inverted[] = {
    // Left
    6, 2, 0,
    0, 4, 6,
    // Right
    1, 3, 7,
    7, 5, 1,
    // Bottom
    5, 4, 0,
    0, 1, 5,
    // Top
    2, 6, 7,
    7, 3, 2,
    // Back
    7, 6, 4,
    4, 5, 7,
    // Front
    0, 2, 3,
    3, 1, 0
};

const float3 cubeVertices2[] = {
    { 0, 0, 1.0f },         //0
    { 1.0f, 0, 1.0f},       //1
    { 0, 1.0f, 1.0f },      //2
    { 1.0f, 1.0f, 1.0f },   //3
    { 0, 0, 0 },            //4
    { 1.0f, 0, 0 },         //5
    { 0, 1.0f, 0 },         //6
    { 1.0f, 1.0f, 0}        //7
};
    /*
    // Left
    0, 2, 6,
    0, 4, 6,
    // Right
    1, 3, 7,
    1, 5, 7,
    // Bottom
    0, 4, 5,
    0, 1, 5,
    // Top
    2, 6, 7,
    2, 3, 7,
    // Back
    4, 6, 7,
    4, 5, 7,
    // Front
    0, 2, 3,
    0, 1, 3*/

/*const float cube_vertices[] = {
    -default_cube_size, -default_cube_size,  default_cube_size,   //0
    default_cube_size, -default_cube_size,  default_cube_size,    //1
    -default_cube_size,  default_cube_size,  default_cube_size,   //2
    default_cube_size,  default_cube_size,  default_cube_size,    //3
    -default_cube_size, -default_cube_size, -default_cube_size,   //4
    default_cube_size, -default_cube_size, -default_cube_size,    //5
    -default_cube_size,  default_cube_size, -default_cube_size,   //6
    default_cube_size,  default_cube_size, -default_cube_size     //7
};*/