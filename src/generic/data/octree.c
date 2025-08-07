
const float octree_scales[] = {
    1.0f,
    0.5f,
    0.25f,
    0.125f,
    0.0625f,
    0.03125f,
    0.015625f,
    0.0078125f
};

const float octree_scales2[] = {
    // 2.0f,
    1.0f,
    0.5f,
    0.25f,
    0.125f,
    0.0625f,
    0.03125f,
    0.015625f,
    0.0078125f
};

const float octree_scales3[] = {
    // 2.0f,
    1.0f,
    0.5f,
    0.25f,
    0.125f,
    0.0625f,
    0.03125f,
    0.015625f,
    0.0078125f
};

#define octree_length 8
// #define octree_node_size 2
const byte octree_node_size = 2;
#define octree_node_size3 (int3) { 2, 2, 2 }



const int3 octree_positions[] = {
    { 0, 0, 0},
    { 0, 0, 1},
    { 0, 1, 0},
    { 0, 1, 1},
    { 1, 0, 0},
    { 1, 0, 1},
    { 1, 1, 0},
    { 1, 1, 1}
};

const byte node_index_with_down[] = {
    -1,
    -1,
    0,
    1,
    -1,
    -1,
    4,
    5
};

const byte node_index_with_up[] = {
    2,
    3,
    -1,
    -1,
    6,
    7,
    -1,
    -1
};

const byte node_index_with_back[] = {
    -1,
    0,
    -1,
    2,
    -1,
    4,
    -1,
    6
};

const byte node_index_with_front[] = {
    1,
    -1,
    3,
    -1,
    5,
    -1,
    7,
    -1
};

const byte node_index_with_left[] = {
    -1,
    -1,
    -1,
    -1,
    0,
    1,
    2,
    3
};

const byte node_index_with_right[] = {
    4,
    5,
    6,
    7,
    -1,
    -1,
    -1,
    -1
};