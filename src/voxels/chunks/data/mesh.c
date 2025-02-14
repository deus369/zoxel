// left
const float3 voxel_face_vertices_left[] = {
    { 0, 0, 0 },    //4
    { 0, 0, 1 },    //0
    { 0, 1, 1 },    //2
    { 0, 1, 0 },    //6
};

// right
const float3 voxel_face_vertices_right[] = {
    { 1, 0, 0 },   //5
    { 1, 0, 1 },   //1
    { 1, 1, 1 },   //3
    { 1, 1, 0 }    //7
};

// down
const float3 voxel_face_vertices_down[] = {
    { 0, 0, 0 },   //4
    { 0, 0, 1 },   //0
    { 1, 0, 1 },   //1
    { 1, 0, 0 },   //5
};

// up
const float3 voxel_face_vertices_up[] = {
    { 0, 1, 0 },   //2
    { 0, 1, 1 },   //0
    { 1, 1, 1 },   //1
    { 1, 1, 0}     //3
};

// back
const float3 voxel_face_vertices_back[] = {
    { 0, 0, 0 },
    { 0, 1, 0 },
    { 1, 1, 0 },
    { 1, 0, 0 }
};

// front
const float3 voxel_face_vertices_front[] = {
    { 0, 0, 1 },
    { 0, 1, 1 },
    { 1, 1, 1 },
    { 1, 0, 1 }
};

const int voxel_face_indicies_length = 6;
const int voxel_face_vertices_length = 4;

const int voxel_face_indicies_p[] = {
    2, 1, 0, 0, 3, 2,   // reversed
    0, 1, 2, 2, 3, 0    // normal
};

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