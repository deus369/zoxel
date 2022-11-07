// mesh data
#define squareSize 0.1f
#define cubeSize 0.5f

const int cubeIndicies3[] =
{
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4
};

// createt cube floats
const float cubeVertices3[] =
{
    -cubeSize, -cubeSize, -cubeSize,    // 0
    -cubeSize,  cubeSize, -cubeSize,    // 1
     cubeSize,  cubeSize, -cubeSize,    // 2
     cubeSize, -cubeSize, -cubeSize,    // 3
    -cubeSize, -cubeSize, cubeSize,     // 4
    -cubeSize,  cubeSize, cubeSize,     // 5
     cubeSize,  cubeSize, cubeSize,     // 6
     cubeSize, -cubeSize, cubeSize      // 7
};

const int cubeIndicies[] =
{
    //Left
    0, 2, 6,
    0, 4, 6,
    //Right
    1, 3, 7,
    1, 5, 7,
    //Bottom
    0, 4, 5,
    0, 1, 5,
    //Top
    2, 6, 7,
    2, 3, 7,
    //Back
    4, 6, 7,
    4, 5, 7,
    //Front
    0, 2, 3,
    0, 1, 3
};

const float cubeVertices[] =
{
    -cubeSize, -cubeSize,  cubeSize,   //0
    cubeSize, -cubeSize,  cubeSize,    //1
    -cubeSize,  cubeSize,  cubeSize,   //2
    cubeSize,  cubeSize,  cubeSize,    //3
    -cubeSize, -cubeSize, -cubeSize,   //4
    cubeSize, -cubeSize, -cubeSize,    //5
    -cubeSize,  cubeSize, -cubeSize,   //6
    cubeSize,  cubeSize, -cubeSize     //7
};

const float3 cubeVertices2[] =
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

const int squareIndicies[] =
{
    0, 1, 2,
    2, 3, 0
};

// createt cube floats
const float squareVerts[] =
{
    -squareSize, -squareSize,
    -squareSize,  squareSize,
     squareSize,  squareSize,
     squareSize, -squareSize
};

// createt cube floats
const float squareVerts3D[] =
{
    -squareSize, -squareSize, -squareSize,
    -squareSize,  squareSize, -squareSize,
     squareSize,  squareSize, -squareSize,
     squareSize, -squareSize, -squareSize
};

// createt cube floats
const float squareUVs[] =
{
    0, 0,
    1, 0,
    1, 1,
    0, 1
};

const float squareTexturedVerts[] = {
    // positions                    // texture coords
    -squareSize, -squareSize,       0, 0,   // top right
    -squareSize, squareSize,        1, 0,   // bottom right
    squareSize, squareSize,         1, 1,   // bottom left
    squareSize,  -squareSize,       0, 1    // top left 
};