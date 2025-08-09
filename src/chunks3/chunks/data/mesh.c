#define voxel_face_indicies_length 6
#define voxel_face_vertices_length 4
#define get_voxel_indicies_1 &voxel_face_indicies_p[0]
#define get_voxel_indicies_0 &voxel_face_indicies_p[6]

// left
static const float3 voxel_face_vertices_0[] = {
    { 0, 0, 0 },    //4
    { 0, 0, 1 },    //0
    { 0, 1, 1 },    //2
    { 0, 1, 0 },    //6
};

// right
static const float3 voxel_face_vertices_1[] = {
    { 1, 0, 0 },   //5
    { 1, 0, 1 },   //1
    { 1, 1, 1 },   //3
    { 1, 1, 0 }    //7
};

// down
static const float3 voxel_face_vertices_2[] = {
    { 0, 0, 0 },   //4
    { 0, 0, 1 },   //0
    { 1, 0, 1 },   //1
    { 1, 0, 0 },   //5
};

// up
static const float3 voxel_face_vertices_3[] = {
    { 0, 1, 0 },   //2
    { 0, 1, 1 },   //0
    { 1, 1, 1 },   //1
    { 1, 1, 0}     //3
};

// back
static const float3 voxel_face_vertices_4[] = {
    { 0, 0, 0 },
    { 0, 1, 0 },
    { 1, 1, 0 },
    { 1, 0, 0 }
};

// front
static const float3 voxel_face_vertices_5[] = {
    { 0, 0, 1 },
    { 0, 1, 1 },
    { 1, 1, 1 },
    { 1, 0, 1 }
};

static const float3* voxel_face_vertices_n[] = {
    voxel_face_vertices_0,
    voxel_face_vertices_1,
    voxel_face_vertices_2,
    voxel_face_vertices_3,
    voxel_face_vertices_4,
    voxel_face_vertices_5
};

static const int voxel_face_indicies_n[] = {
    // X
    0, 1, 2, 2, 3, 0,   // normal
    2, 1, 0, 0, 3, 2,   // reversed

    // Y
    2, 1, 0, 0, 3, 2,   // reversed
    0, 1, 2, 2, 3, 0,   // normal

    // Z
    0, 1, 2, 2, 3, 0,   // normal
    2, 1, 0, 0, 3, 2,   // reversed
};

const int voxel_face_indicies_p[] = {
    2, 1, 0, 0, 3, 2,   // reversed
    0, 1, 2, 2, 3, 0    // normal
};

static inline const int* get_voxel_indices(byte is_positive) {
    if (is_positive) {
        return &voxel_face_indicies_p[0];
    } else {
        return &voxel_face_indicies_p[6];
    }
}

// Face normals for dynamic lighting
static const float3 face_normals[6] = {
    { -1, 0, 0 }, // direction_left
    { 1, 0, 0 },  // direction_right
    { 0, -1, 0 }, // direction_down
    { 0, 1, 0 },  // direction_up
    { 0, 0, -1 }, // direction_back
    { 0, 0, 1 }   // direction_front
};

static const int voxel_cube_indicies[] = {
    //Left
    0, 2, 6,    0, 4, 6,
    //Right
    1, 3, 7,    1, 5, 7,
    //Bottom
    0, 4, 5,    0, 1, 5,
    //Top
    2, 6, 7,    2, 3, 7,
    //Back
    4, 6, 7,    4, 5, 7,
    //Front
    0, 2, 3,    0, 1, 3
};

static const float3 voxel_cube_vertices[] = {
    { 0, 0, 1.0f },         //0
    { 1.0f, 0, 1.0f},       //1
    { 0, 1.0f, 1.0f },      //2
    { 1.0f, 1.0f, 1.0f },   //3
    { 0, 0, 0 },            //4
    { 1.0f, 0, 0 },         //5
    { 0, 1.0f, 0 },         //6
    { 1.0f, 1.0f, 0}        //7
};