// mesh data

const float squareSize = 0.1f;
// createt cube floats
const float squareVerts[] =
{
    -squareSize, -squareSize,
    -squareSize,  squareSize,
     squareSize,  squareSize,
     squareSize, -squareSize
};
const float squareVerts2[] =
{
    -squareSize, -squareSize,
    -squareSize,  squareSize * 2.0,
     squareSize,  squareSize,
     squareSize, -squareSize
};

const int squareTexturedIndicies2[] =
{
    0, 1, 2,
    2, 3, 0
};

// createt cube floats
const float squareUVs[] =
{
    0, 0,
    1, 0,
    1, 1,
    0, 1
};

const int squareTexturedIndicies[] =
{
    0, 1, 2,
    2, 3, 0
};

float squareTexturedVerts[] = {
    // positions                    // texture coords
    -squareSize, -squareSize,       0, 0,   // top right
    -squareSize, squareSize * 1.4,        1, 0,   // bottom right
    squareSize, squareSize * 1.4,         1, 1,   // bottom left
    squareSize,  -squareSize,       0, 1    // top left 
};