#define octree_length 8
#define octree_node_size 2
#define octree_node_size3 (int3) { 2, 2, 2 }

#define direction_left 0
#define direction_right 1
#define direction_down 2
#define direction_up 3
#define direction_back 4
#define direction_front 5

/*int getAdjacentIndex(unsigned int node_index, unsigned char direction)
{
    int x = node_index & 1;
    int y = (node_index >> 1) & 1;
    int z = (node_index >> 2) & 1;
    switch (direction) {
        case 0:
            x = x == 0 ? 1 : 0;
            break;
        case 1:
            x = x == 0 ? 1 : 0;
            break;
        case 2: // down
            y = y == 0 ? 1 : 0;
            break;
        case 3: // up
            y = y == 0 ? 1 : 0;
            break;
        case 4:
            z = z == 0 ? 1 : 0;
            break;
        case 5:
            z = z == 0 ? 1 : 0;
            break;
    }
    return (x | (y << 1) | (z << 2));
}*/


#define zoxel_octree_component(name, type, default_value)\
typedef struct name name;\
typedef struct name\
{\
    type value;\
    name *nodes;\
} name;\
ECS_COMPONENT_DECLARE(name);\
void free##_##name(name* octree)\
{\
    if (octree->nodes != NULL)\
    {\
        for (unsigned char i = 0; i < octree_length; i++)\
        {\
            free##_##name(&octree->nodes[i]);\
        }\
        free(octree->nodes);\
        octree->nodes = NULL;\
    }\
}\
void clone##_##name(name* dst, name* src)\
{\
    dst->value = src->value;\
    if (src->nodes)\
    {\
        dst->nodes = malloc(sizeof(name) * octree_length);\
        for (int i = 0; i < octree_length; i++)\
        {\
            clone##_##name(&dst->nodes[i], &src->nodes[i]);\
        }\
    }\
    else\
    {\
        dst->nodes = NULL;\
    }\
}\
void open##_##name(name* octree)\
{\
    if (octree->nodes == NULL)\
    {\
        octree->nodes = malloc(sizeof(name) * octree_length);\
        for (unsigned char i = 0; i < octree_length; i++)\
        {\
            octree->nodes[i].nodes = NULL;\
            octree->nodes[i].value = default_value;\
        }\
    }\
}\
void close##_##name(name* octree)\
{\
    free##_##name(octree);\
}\
ECS_CTOR(name, ptr,\
{\
    ptr->nodes = NULL;\
    ptr->value = default_value;\
})\
ECS_DTOR(name, ptr,\
{\
    free##_##name(ptr);\
})\
ECS_MOVE(name, dst, src,\
{\
    dst->value = src->value;\
    dst->nodes = src->nodes;\
    src->nodes = NULL;\
    src->value = default_value;\
})\
ECS_COPY(name, dst, src, {\
    free##_##name(dst);\
    clone##_##name(dst, src);\
})\
const name* null_if_open##_##name(const name* node)\
{\
    if (node->nodes != NULL)\
    {\
        return NULL;\
    }\
    return node;\
}\
const name* find_node##_##name(const name* node, int3 octree_position, unsigned char depth)\
{\
    if (depth == 0)\
    {\
        if (node->nodes != NULL)\
        {\
            return NULL;\
        }\
        return node;\
    }\
    if (node->nodes == NULL)\
    {\
        return node;\
    }\
    depth--;\
    unsigned char dividor = pow(2, depth);\
    int3 local_position = (int3) { octree_position.x / dividor, octree_position.y / dividor, octree_position.z / dividor };\
    int3 child_octree_position = (int3) { octree_position.x % dividor, octree_position.y % dividor, octree_position.z % dividor };\
    unsigned char child_index = local_position.x * 4 + local_position.y * 2 + local_position.z;\
    node = &node->nodes[child_index];\
    return find_node##_##name(node, child_octree_position, depth);\
}\
const name* find_adjacent##_##name(const name* root, const name* node, int3 octree_position, int3 node_position, unsigned char depth, unsigned char direction)\
{\
    if (node == NULL || node->nodes == NULL)\
    {\
        return NULL;\
    }\
    if (direction == direction_left)\
    {\
        if (node_position.x != 0)\
        {\
            node_position.x--;\
            return null_if_open##_##name(&node->nodes[node_position.x * 4 + node_position.y * 2 + node_position.z]);\
        }\
        octree_position.x--;\
    }\
    else if (direction == direction_right)\
    {\
        if (node_position.x != 1)\
        {\
            node_position.x++;\
            return null_if_open##_##name(&node->nodes[node_position.x * 4 + node_position.y * 2 + node_position.z]);\
        }\
        octree_position.x++;\
    }\
    else if (direction == direction_down)\
    {\
        if (node_position.y != 0)\
        {\
            node_position.y--;\
            return null_if_open##_##name(&node->nodes[node_position.x * 4 + node_position.y * 2 + node_position.z]);\
        }\
        octree_position.y--;\
    }\
    else if (direction == direction_up)\
    {\
        if (node_position.y != 1)\
        {\
            node_position.y++;\
            return null_if_open##_##name(&node->nodes[node_position.x * 4 + node_position.y * 2 + node_position.z]);\
        }\
        octree_position.y++;\
    }\
    else if (direction == direction_back)\
    {\
        if (node_position.z != 0)\
        {\
            node_position.z--;\
            return null_if_open##_##name(&node->nodes[node_position.x * 4 + node_position.y * 2 + node_position.z]);\
        }\
        octree_position.z--;\
    }\
    else if (direction == direction_front)\
    {\
        if (node_position.z != 1)\
        {\
            node_position.z++;\
            return null_if_open##_##name(&node->nodes[node_position.x * 4 + node_position.y * 2 + node_position.z]);\
        }\
        octree_position.z++;\
    }\
    unsigned char position_bounds = pow(2, depth);\
    if (octree_position.x >= 0 && octree_position.x < position_bounds\
        && octree_position.y >= 0 && octree_position.y < position_bounds\
        && octree_position.z >= 0 && octree_position.z < position_bounds)\
    {\
        return find_node##_##name(root, octree_position, depth);\
    }\
    else\
    {\
        return NULL;\
    }\
}

/*
    printf("octree_position [%ix%ix%i] depth [%i] dividor[%i] local_position [%ix%ix%i]\n", octree_position.x, octree_position.y, octree_position.z, depth, dividor, local_position.x, local_position.y, local_position.z);\
    

    int3 local_position = (int3) { octree_position.x & 1, octree_position.y & 1, octree_position.z & 1 };\
    octree_position.x >>= 1;\
    octree_position.y >>= 1;\
    octree_position.z >>= 1;\

        printf("bounds [%i] depth [%i]\n", position_bounds, depth);\

        return node;\


    // if (child_index >= 8) return NULL;\
    return NULL;\

    int3 local_position = (int3) { octree_position.x / 2, octree_position.y / 2, octree_position.z / 2 };\
    return NULL;\

    octree_position.x %= 2;\
    octree_position.y %= 2;\
    octree_position.z %= 2;\

    if (node_index == 255)\
    {\
        return NULL;\
    }\

    int x = (node_index / 4) % 2;\
    int y = (node_index / 2) % 2;\
    int z = node_index % 2;\

    unsigned char global_position = x * pow(2, depth) + y * pow(2, depth-1) + (z * pow(2, depth-2));\
    const name* current_node = root;\
    for (unsigned char i = 0; i < depth; i++)\
    {\
        current_node = &current_node->nodes[(global_position >> i) & 1];\
    }\
    if (current_node == root)\
    {\
        return NULL;\
    }\
    return current_node;\

    unsigned char global_position = x * pow(2, depth) + y * pow(2, depth-1) + z;\
    const name* current_node = root;\
    for (unsigned char i = 0; i < depth; i++)\
    {\
        current_node = &current_node->nodes[(global_position / ((int) pow(2, i))) % 2];\
    }\
    return current_node;\

    if (node_index == 0)\
    {\
        if (direction == direction_up)\
        {\
            return null_if_open##_##name(&parent_node->nodes[2]);\
        }\
        else if (direction == direction_right)\
        {\
            return null_if_open##_##name(&parent_node->nodes[4]);\
        }\
        else if (direction == direction_front)\
        {\
            return null_if_open##_##name(&parent_node->nodes[1]);\
        }\
    }\
    else if (node_index == 1)\
    {\
        if (direction == direction_up)\
        {\
            return null_if_open##_##name(&parent_node->nodes[3]);\
        }\
        else if (direction == direction_right)\
        {\
            return null_if_open##_##name(&parent_node->nodes[5]);\
        }\
        else if (direction == direction_back)\
        {\
            return null_if_open##_##name(&parent_node->nodes[0]);\
        }\
    }\
    else if (node_index == 2)\
    {\
        if (direction == direction_down)\
        {\
            return null_if_open##_##name(&parent_node->nodes[0]);\
        }\
        else if (direction == direction_right)\
        {\
            return null_if_open##_##name(&parent_node->nodes[6]);\
        }\
        else if (direction == direction_front)\
        {\
            return null_if_open##_##name(&parent_node->nodes[3]);\
        }\
    }\
    else if (node_index == 3)\
    {\
        if (direction == direction_down)\
        {\
            return null_if_open##_##name(&parent_node->nodes[1]);\
        }\
        else if (direction == direction_right)\
        {\
            return null_if_open##_##name(&parent_node->nodes[7]);\
        }\
        else if (direction == direction_back)\
        {\
            return null_if_open##_##name(&parent_node->nodes[2]);\
        }\
    }\
    else if (node_index == 4)\
    {\
        if (direction == direction_up)\
        {\
            return null_if_open##_##name(&parent_node->nodes[6]);\
        }\
        else if (direction == direction_left)\
        {\
            return null_if_open##_##name(&parent_node->nodes[0]);\
        }\
        else if (direction == direction_front)\
        {\
            return null_if_open##_##name(&parent_node->nodes[5]);\
        }\
    }\
    else if (node_index == 5)\
    {\
        if (direction == direction_up)\
        {\
            return null_if_open##_##name(&parent_node->nodes[7]);\
        }\
        else if (direction == direction_left)\
        {\
            return null_if_open##_##name(&parent_node->nodes[1]);\
        }\
        else if (direction == direction_back)\
        {\
            return null_if_open##_##name(&parent_node->nodes[4]);\
        }\
    }\
    else if (node_index == 6)\
    {\
        if (direction == direction_down)\
        {\
            return null_if_open##_##name(&parent_node->nodes[4]);\
        }\
        else if (direction == direction_left)\
        {\
            return null_if_open##_##name(&parent_node->nodes[2]);\
        }\
        else if (direction == direction_front)\
        {\
            return null_if_open##_##name(&parent_node->nodes[7]);\
        }\
    }\
    else if (node_index == 7)\
    {\
        if (direction == direction_down)\
        {\
            return null_if_open##_##name(&parent_node->nodes[5]);\
        }\
        else if (direction == direction_left)\
        {\
            return null_if_open##_##name(&parent_node->nodes[3]);\
        }\
        else if (direction == direction_back)\
        {\
            return null_if_open##_##name(&parent_node->nodes[6]);\
        }\
    }\
*/
/*const int3 octree_positions[] =
{
    { 0, 0, 0}, 0
    { 0, 0, 1}, 1
    { 0, 1, 0}, 2
    { 0, 1, 1}, 3
    { 1, 0, 0}, 4
    { 1, 0, 1}, 5
    { 1, 1, 0}, 6
    { 1, 1, 1}  7
};*/
/*x = (1 / 4) % 2 = 0
y = (1 / 2) % 2 = 0
z = 1 % 2 = 1
x = (2 / 4) % 2 = 0
y = (2 / 2) % 2 = 1
z = 2 % 2 = 0
x = (4 / 4) % 2 = 1
y = (4 / 2) % 2 = 0
z = 4 % 2 = 0*/
/*x = 1 % 2 = 1
y = (1 / 2) % 2 = 0
z = (1 / 4) % 2 = 0
x = 6 % 2 = 1
y = (6 / 2) % 2 = 1
z = (6 / 4) % 2 = 0
x = 7 % 2 = 1
y = (7 / 2) % 2 = 1
z = (7 / 4) % 2 = 1*/

/*
    node_index = getAdjacentIndex(node_index, direction);\
    const name* current_node = root;\
    unsigned char currDepth = 0;\
    while (currDepth != depth)\
    {\
        if (current_node->nodes == NULL)\
        {\
            return current_node;\
        }\
        unsigned char childIndex = node_index & 7;\
        current_node = &current_node->nodes[childIndex];\
        node_index = node_index >> 3;\
        currDepth++;\
    }\
    return current_node;\
*/
    /*unsigned char adjacentNodeIndex = getAdjacentIndex(node_index, direction);\
    unsigned char childIndex = adjacentNodeIndex & 7;\
    if (childIndex >= 8)\
    {\
        return NULL;\
    }\
    return &current_node->nodes[childIndex];*/

// ^ above function doesn't work atm

// return current_node;
// return current_node;
//  return NULL;

#define zoxel_octree_component_define(name)\
    ECS_COMPONENT_DEFINE(world, name);\
    ecs_set_hooks(world, name, {\
        .ctor = ecs_ctor(name),\
        .move = ecs_move(name),\
        .copy = ecs_copy(name),\
        .dtor = ecs_dtor(name)\
    });

/*typedef struct ChunkOctree ChunkOctree;
typedef struct ChunkOctree
{
    unsigned char value;
    ChunkOctree *nodes;
} ChunkOctree;*/