#define octree_length 8
// #define octree_node_size 2
const byte octree_node_size = 2;
#define octree_node_size3 (int3) { 2, 2, 2 }
#define direction_left 0
#define direction_right 1
#define direction_down 2
#define direction_up 3
#define direction_back 4
#define direction_front 5
// debugging
int node_memory = 0;

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
    2.0f,
    1.0f,
    0.5f,
    0.25f,
    0.125f,
    0.0625f,
    0.03125f,
    0.015625f,
    0.0078125f
};

const byte powers_of_two_byte[] = {
    1,
    2,
    4,
    8,
    16,
    32,
    64,
    128
};

const float powers_of_two[] = {
    1,
    2,
    4,
    8,
    16,
    32,
    64,
    128,
    256,
    512,
    1024,
    2048
};

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

static inline int next_power_of_two(int n) {
    if (n <= 0) {
        return 1;
    }
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

static inline int next_power_of_two_root_safe(int n) {
    if (n <= 0) {
        return 1;
    }
    int root = 1;
    while (root * root < n) {
        root *= 2;
    }
    return root;
}

// Only works if `n` is under ~2^30
static inline int next_power_of_two_root(int n) {
    if (n <= 0) return 1;
    int log2val = (int)ceil(log2(n) / 2.0);
    return 1 << log2val;
}

/*static inline int next_power_of_two(int n) {
    int count = 1;
    int power = 1;
    while (power < n) {
        power *= 2;
        count++;
    }
    return count;
}*/
