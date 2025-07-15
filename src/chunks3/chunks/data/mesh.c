// left
const float3 voxel_face_vertices_0[] = {
    { 0, 0, 0 },    //4
    { 0, 0, 1 },    //0
    { 0, 1, 1 },    //2
    { 0, 1, 0 },    //6
};

// right
const float3 voxel_face_vertices_1[] = {
    { 1, 0, 0 },   //5
    { 1, 0, 1 },   //1
    { 1, 1, 1 },   //3
    { 1, 1, 0 }    //7
};

// down
const float3 voxel_face_vertices_2[] = {
    { 0, 0, 0 },   //4
    { 0, 0, 1 },   //0
    { 1, 0, 1 },   //1
    { 1, 0, 0 },   //5
};

// up
const float3 voxel_face_vertices_3[] = {
    { 0, 1, 0 },   //2
    { 0, 1, 1 },   //0
    { 1, 1, 1 },   //1
    { 1, 1, 0}     //3
};

// back
const float3 voxel_face_vertices_4[] = {
    { 0, 0, 0 },
    { 0, 1, 0 },
    { 1, 1, 0 },
    { 1, 0, 0 }
};

// front
const float3 voxel_face_vertices_5[] = {
    { 0, 0, 1 },
    { 0, 1, 1 },
    { 1, 1, 1 },
    { 1, 0, 1 }
};

const float3* voxel_face_vertices_n[] = {
    voxel_face_vertices_0,
    voxel_face_vertices_1,
    voxel_face_vertices_2,
    voxel_face_vertices_3,
    voxel_face_vertices_4,
    voxel_face_vertices_5
};

const int voxel_face_indicies_length = 6;
const int voxel_face_vertices_length = 4;

const int voxel_face_indicies_p[] = {
    2, 1, 0, 0, 3, 2,   // reversed
    0, 1, 2, 2, 3, 0    // normal
};

const int* get_voxel_indices(byte is_positive) {
    if (is_positive) {
        return &voxel_face_indicies_p[0];
    } else {
        return &voxel_face_indicies_p[6];
    }
}

#define get_voxel_indicies_1 &voxel_face_indicies_p[0]
#define get_voxel_indicies_0 &voxel_face_indicies_p[6]

const int voxel_cube_indicies[] = {
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

const float3 voxel_cube_vertices[] = {
    { 0, 0, 1.0f },         //0
    { 1.0f, 0, 1.0f},       //1
    { 0, 1.0f, 1.0f },      //2
    { 1.0f, 1.0f, 1.0f },   //3
    { 0, 0, 0 },            //4
    { 1.0f, 0, 0 },         //5
    { 0, 1.0f, 0 },         //6
    { 1.0f, 1.0f, 0}        //7
};