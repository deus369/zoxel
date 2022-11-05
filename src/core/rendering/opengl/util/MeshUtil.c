// mesh data

const float squareSize = 0.1f;
const float cubeSize = 0.5f;

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
    //Top
    2, 6, 7,
    2, 3, 7,
    //Bottom
    0, 4, 5,
    0, 1, 5,
    //Left
    0, 2, 6,
    0, 4, 6,
    //Right
    1, 3, 7,
    1, 5, 7,
    //Front
    0, 2, 3,
    0, 1, 3,
    //Back
    4, 6, 7,
    4, 5, 7
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
    { -1, -1,  1 },   //0
    { 1, -1,  1 },    //1
    { -1,  1,  1 },   //2
    { 1,  1,  1 },    //3
    { -1, -1, -1 },   //4
    { 1, -1, -1 },    //5
    { -1,  1, -1 },   //6
    { 1,  1, -1 }     //7
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

float squareTexturedVerts[] = {
    // positions                    // texture coords
    -squareSize, -squareSize,       0, 0,   // top right
    -squareSize, squareSize,        1, 0,   // bottom right
    squareSize, squareSize,         1, 1,   // bottom left
    squareSize,  -squareSize,       0, 1    // top left 
};