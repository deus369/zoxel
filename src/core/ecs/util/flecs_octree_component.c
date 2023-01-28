#define octree_length 8
#define octree_node_size 2
#define octree_node_size3 (int3) { 2, 2, 2 }

#define direction_left 0
#define direction_right 1
#define direction_down 2
#define direction_up 3
#define direction_back 4
#define direction_front 5

int getAdjacentIndex(unsigned int node_index, unsigned char direction)
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
}


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
const name* find_adjacent##_##name(const name* parent_node, unsigned int node_index, unsigned char depth, unsigned char direction, const name* root)\
{\
    if (node_index == 255)\
    {\
        return NULL;\
    }\
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
    return NULL;\
}

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