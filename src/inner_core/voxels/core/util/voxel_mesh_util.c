const int voxel_cube_indicies[] =
{
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

const float3 voxel_cube_vertices[] =
{
    { 0, 0, 1.0f },         //0
    { 1.0f, 0, 1.0f},       //1
    { 0, 1.0f, 1.0f },      //2
    { 1.0f, 1.0f, 1.0f },   //3
    { 0, 0, 0 },            //4
    { 1.0f, 0, 0 },         //5
    { 0, 1.0f, 0 },         //6
    { 1.0f, 1.0f, 0}        //7
};

// left
const int voxel_face_indicies_left_length = 6;
const int voxel_face_indicies_left[] =
{
    // 0, 1, 3,    0, 2, 3,
    0, 1, 2,    2, 3, 0,
};
const int voxel_face_vertices_left_length = 4;
const float3 voxel_face_vertices_left[] =
{
    { 0, 0, 0 },            //4
    { 0, 0, 1.0f },         //0
    { 0, 1.0f, 1.0f },      //2
    { 0, 1.0f, 0 },         //6
};

// right
const int voxel_face_indicies_right_length = 6;
const int voxel_face_indicies_right[] =
{
    // 0, 1, 3,    0, 2, 3,
    0, 1, 2,    2, 3, 0,
};
const int voxel_face_vertices_right_length = 4;
const float3 voxel_face_vertices_right[] =
{
    { 1.0f, 0, 0 },         //5
    { 1.0f, 0, 1.0f},       //1
    { 1.0f, 1.0f, 1.0f },   //3
    { 1.0f, 1.0f, 0}        //7
};

// down
const int voxel_face_indicies_down_length = 6;
const int voxel_face_indicies_down[] =
{
    // 0, 2, 3,    0, 1, 3,
    0, 1, 2,    2, 3, 0,
};
const int voxel_face_vertices_down_length = 4;
const float3 voxel_face_vertices_down[] =
{
    { 0, 0, 0 },            //4
    { 0, 0, 1.0f },         //0
    { 1.0f, 0, 1.0f},       //1
    { 1.0f, 0, 0 },         //5
};

// up
const int voxel_face_indicies_up_length = 6;
const int voxel_face_indicies_up[] =
{
    // 0, 2, 3,    0, 1, 3,
    0, 1, 2,    2, 3, 0,
};
const int voxel_face_vertices_up_length = 4;
const float3 voxel_face_vertices_up[] =
{
    { 0, 1.0f, 0 },         //2
    { 0, 1.0f, 1.0f },      //0
    { 1.0f, 1.0f, 1.0f },   //1
    { 1.0f, 1.0f, 0}        //3
};
const float2 voxel_face_uvs_up[] =
{
    { 0, 0.0f },
    { 0.0f, 1.0f },
    { 1.0f, 1.0f },
    { 1.0f, 0 }
};

// back
const int voxel_face_indicies_back_length = 6;
const int voxel_face_indicies_back[] =
{
    // 0, 2, 3,    0, 1, 3,
    0, 1, 2,    2, 3, 0,
};
const int voxel_face_vertices_back_length = 4;
const float3 voxel_face_vertices_back[] =
{
    /*{ 0, 0, 0 },            //4
    { 1.0f, 0, 0 },         //5
    { 0, 1.0f, 0 },         //6
    { 1.0f, 1.0f, 0}        //7*/
    { 0, 0, 0.0f },
    { 0.0f, 1.0f, 0.0f},
    { 1.0f, 1.0f, 0.0f },
    { 1.0f, 0.0f, 0.0f }
};

// front
const int voxel_face_indicies_front_length = 6;
const int voxel_face_indicies_front[] =
{
    // 0, 2, 3,    0, 1, 3
    0, 1, 2,    2, 3, 0,
};
const int voxel_face_vertices_front_length = 4;
const float3 voxel_face_vertices_front[] =
{
    /*{ 0, 0, 1.0f },         //0
    { 1.0f, 0, 1.0f},       //1
    { 0, 1.0f, 1.0f },      //2
    { 1.0f, 1.0f, 1.0f }    //3*/
    { 0, 0, 1.0f },
    { 0.0f, 1.0f, 1.0f},
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 0.0f, 1.0f }
};