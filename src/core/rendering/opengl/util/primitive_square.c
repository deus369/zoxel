#define squareSize 0.1f

const int square_indicies[] =
{
    0, 1, 2,
    2, 3, 0
};

// createt cube floats
const float square_vertices[] =
{
    -squareSize, -squareSize,
    -squareSize,  squareSize,
     squareSize,  squareSize,
     squareSize, -squareSize
};

const float square_vertices2[] =
{
    -1, -1,
    -1, 1,
    1, 1,
    1, -1
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

const float squareTexturedVerts2[] = {
    // positions    // texture coords
    /*-1, -1,         0, 0,   // top right
    -1, 1,          1, 0,   // bottom right
    1, 1,           1, 1,   // bottom left
    1, -1,         0, 1    // top left 
    */

    0, 0,         0, 0,   // top right
    0, 1,          1, 0,   // bottom right
    1, 1,           1, 1,   // bottom left
    1, 0,         0, 1    // top left 
};