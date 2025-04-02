const int cube_indicies_length = 36;
const int cube_indicies[] = {
    0, 2, 6, 6, 4, 0,   // Left
    7, 3, 1, 1, 5, 7,   // Right
    0, 4, 5, 5, 1, 0,   // Bottom
    7, 6, 2, 2, 3, 7,   // Top
    4, 6, 7, 7, 5, 4,   // Back
    3, 2, 0, 0, 1, 3    // Front
};

// centred cube verts
const int cube_vertices_length = 8;
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

const int cube_uvs_length = 8;
const float2 cube_uvs[] = {
    (float2) { 0, 0 },   //0
    (float2) { 0, 1 },   //1
    (float2) { 1, 0 },   //2
    (float2) { 1, 1 },   //3
    (float2) { 0, 0 },   //4
    (float2) { 0, 1 },   //5
    (float2) { 1, 0 },   //6
    (float2) { 1, 1 },   //7
};

const int cube_vertices_f_length = 8 * 3;
// vertex cube floats
const float cube_vertices_f[] = {
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
const float cube_vertices_inverted[] = {
    -default_cube_size, -default_cube_size,  default_cube_size,   //0
    default_cube_size, -default_cube_size,  default_cube_size,    //1
    -default_cube_size,  default_cube_size,  default_cube_size,   //2
    default_cube_size,  default_cube_size,  default_cube_size,    //3
    -default_cube_size, -default_cube_size, -default_cube_size,   //4
    default_cube_size, -default_cube_size, -default_cube_size,    //5
    -default_cube_size,  default_cube_size, -default_cube_size,   //6
    default_cube_size,  default_cube_size, -default_cube_size     //7
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
// inverted
const int cube_indicies_inverted[] = {
    6, 2, 0, 0, 4, 6,   // Left
    1, 3, 7, 7, 5, 1,   // Right
    5, 4, 0, 0, 1, 5,   // Bottom
    2, 6, 7, 7, 3, 2,   // Top
    7, 6, 4, 4, 5, 7,   // Back
    0, 2, 3, 3, 1, 0    // Front
};


/*const int cubeIndicies3[] = {
-    0, 1, 2,
-    2, 3, 0,
-    4, 5, 6,
-    6, 7, 4
-};*/
/*0, 2, 6,    0, 4, 6,    //Left
 1 , 3, 7,    1, 5, 7,    //Right  *
 0, 4, 5,    0, 1, 5,    //Bottom
 2, 6, 7,    2, 3, 7,    //Top
 4, 6, 7,    4, 5, 7,    //Back
 0, 2, 3,    0, 1, 3     //Front*/