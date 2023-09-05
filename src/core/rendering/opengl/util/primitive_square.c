#define squareSize 0.1f

const int square_indicies[] = {
    2, 1, 0,    0, 3, 2
};

const float square_vertices2[] = {
    -1, -1,
    -1, 1,
    1, 1,
    1, -1
};

// createt cube floats
const float squareVerts3D[] = {
    -squareSize, -squareSize, -squareSize,
    -squareSize,  squareSize, -squareSize,
     squareSize,  squareSize, -squareSize,
     squareSize, -squareSize, -squareSize
};

// createt cube floats
const float squareUVs[] = {
    0, 0,
    1, 0,
    1, 1,
    0, 1
};

const float squareTexturedVerts[] = {
    -squareSize, -squareSize,       0, 0,   // top right
    -squareSize, squareSize,        1, 0,   // bottom right
    squareSize, squareSize,         1, 1,   // bottom left
    squareSize,  -squareSize,       0, 1    // top left 
};

const float squareTexturedVerts2[] = {
    0, 0,         0, 0,   // top right
    0, 1,         0, 1,   // bottom right
    1, 1,         1, 1,   // bottom left
    1, 0,         1, 0    // top left 
};

const float2 square_vertices[] = {
    { -0.5f, -0.5f },
    { -0.5f, 0.5f },
    { 0.5f, 0.5f },
    { 0.5f, -0.5f }
};

// where y is centred
const float2 square_vertices_right_aligned[] = {
    { -1, -0.5f },
    { -1, 0.5f },
    { 0, 0.5f },
    { 0, -0.5f }
};
const float2 square_vertices_left_aligned[] = {
    { 0, -0.5f },
    { 0, 0.5f },
    { 1, 0.5f },
    { 1, -0.5f }
};

const float2* get_aligned_mesh2D(unsigned char alignment) {
    if (alignment == zox_mesh_alignment_centred) {
        return square_vertices;
    } else if (alignment == zox_mesh_alignment_right) {
        return square_vertices_right_aligned;
    } else if (alignment == zox_mesh_alignment_left) {
        return square_vertices_left_aligned;
    } else {
        return square_vertices;
    }
}

const float2 square_uvs[] = {
    { 0, 0 },       // top right
    { 0, 1 },       // bottom right
    { 1, 1 },       // bottom left
    { 1, 0 }       // top left 
};

/*const float2 square_vertices[] = {
    { 0, 0 },       // top right
    { 0, 1 },       // bottom right
    { 1, 1 },       // bottom left
    { 1, 0 }       // top left 
};

const float2 square_vertices_right_aligned[] = {
    { -0.5f, -0.5f },
    { -0.5f, 0.5f },
    { 0.5f, 0.5f },
    { 0.5f, -0.5f }
};*/
