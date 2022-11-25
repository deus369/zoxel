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