#define zoxel_octree_component_define2(name, ...)\
zox_define_component(name)\
ecs_set_hooks(world, name, {\
    .ctor = ecs_ctor(name),\
    .move = ecs_move(name),\
    .copy = ecs_copy(name),\
    /*.dtor = ecs_dtor(name),*/\
});\\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

#define zoxel_octree_component_define(name) zox_define_entities_component2(name, [out] name)

// __attribute__((aligned(9)))

// structs used for voxels at max depth

// todo: if nodes is at end, instead of making nodes 8 length, make single! idk yet... this refactors hard

//  > each node needs children links, if a parent
//  > each node needs a value
//  > each node can have extra values for voxel entity links
//      > when setting set_voxel we can open node of different type here
//          > make a open node function that allocates final nodes to a single VoxelEntityLink structure
//          > when spawning block vox, set link inside it
//      > when closing a node with entity, also destroy that entity, closing would need to pass in voxel information then for struct types per voxel type
//      >

// links to node and child nodes, using entity component to find depth
// if less then max depth, this is null or 8 length
// if max depth, this is assigned to a value node
/* typedef struct {
    void *node;
} Node;

typedef struct {
    unsigned char value;
} VoxelNode; */

// used to link static chunk voxel to a entity in world
typedef struct {
    ecs_entity_t value;
} VoxelEntityLink;


#define zoxel_octree_component(name, type, default_value)\
typedef struct name name;\
struct name {\
    type value;\
    name *nodes;\
}; ECS_COMPONENT_DECLARE(name);\
\
void close_##name(name* octree) {\
    if (!octree->nodes) return;\
    /* > todo: check if entity link here, using depth check */\
    for (unsigned char i = 0; i < octree_length; i++) close_##name(&octree->nodes[i]);\
    free(octree->nodes);\
    octree->nodes = NULL;\
    node_memory -= 1;\
    /*zox_log(" > freeing node [%i]\n", (sizeof(name) * octree_length))*/\
}\
\
void open_new_##name(name* octree) {\
    /*zoxel_log(" > opening node [%i + 1 = %i :: %i]\n", sizeof(name*), sizeof(name), (sizeof(name) * octree_length));*/\
    octree->nodes = malloc(sizeof(name) * octree_length);\
    node_memory += 1;\
}\
\
void clone_##name(name* dst, const name* src) {\
    dst->value = src->value;\
    if (src->nodes) {\
        open_new_##name(dst);\
        for (unsigned char i = 0; i < octree_length; i++) clone_##name(&dst->nodes[i], &src->nodes[i]);\
    } else {\
        dst->nodes = NULL;\
    }\
}\
\
void clone_depth_##name(name* dst, const name* src, const unsigned char max_depth, unsigned char depth) {\
    dst->value = src->value;\
    depth++;\
    if (src->nodes && depth <= max_depth) {\
        open_new_##name(dst);\
        for (unsigned char i = 0; i < octree_length; i++) clone_depth_##name(&dst->nodes[i], &src->nodes[i], max_depth, depth);\
    } else {\
        dst->nodes = NULL;\
    }\
}\
\
void open##_##name(name* octree) {\
    if (octree->nodes == NULL) {\
        open_new_##name(octree);\
        for (unsigned char i = 0; i < octree_length; i++) octree->nodes[i].nodes = NULL;\
    }\
}\
\
const name* find_node##_##name(const name* node, int3 octree_position, unsigned char depth) {\
    /* if depth finish or if closed node, return node early */ \
    if (depth == 0 || node->nodes == NULL) return node;\
    depth--;\
    unsigned char dividor = powers_of_two[depth];\
    int3 local_position = (int3) { octree_position.x / dividor, octree_position.y / dividor, octree_position.z / dividor };\
    int3 child_octree_position = (int3) { octree_position.x % dividor, octree_position.y % dividor, octree_position.z % dividor };\
    return find_node##_##name(&node->nodes[int3_to_node_index(local_position)], child_octree_position, depth);\
}\
\
/* maybe make below function use this if it isn't in the non root node */\
const name* find_root_adjacent##_##name(const name* root, int3 position, unsigned char depth, unsigned char direction, const name *neighbors[], unsigned char *chunk_index) {\
    if (direction == direction_left) position.x--;\
    else if (direction == direction_right) position.x++;\
    else if (direction == direction_down) position.y--;\
    else if (direction == direction_up) position.y++;\
    else if (direction == direction_back) position.z--;\
    else if (direction == direction_front) position.z++;\
    unsigned char position_bounds = powers_of_two[depth];\
    if (position.x >= 0 && position.x < position_bounds && position.y >= 0 && position.y < position_bounds && position.z >= 0 && position.z < position_bounds) {\
        return find_node##_##name(root, position, depth);\
    } else {\
        /* special case for adjacent nodes, flips position and crosses to neighbor chunk */\
        *chunk_index = direction + 1;\
        if (direction == direction_left) {\
            if (neighbors[direction] != NULL) {\
                position.x = position_bounds - 1;\
                return find_node##_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_right) {\
            if (neighbors[direction] != NULL) {\
                position.x = 0;\
                return find_node##_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_down) {\
            if (neighbors[direction] != NULL) {\
                position.y = position_bounds - 1;\
                return find_node##_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_up) {\
            if (neighbors[direction] != NULL) {\
                position.y = 0;\
                return find_node##_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_back) {\
            if (neighbors[direction] != NULL) {\
                position.z = position_bounds - 1;\
                return find_node##_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_front) {\
            if (neighbors[direction] != NULL) {\
                position.z = 0;\
                return find_node##_##name(neighbors[direction], position, depth);\
            }\
        }\
        return NULL;\
    }\
}\
\
const name* find_adjacent##_##name(const name* root, const name* node, int3 position, unsigned char node_index, byte3 node_position,\
    unsigned char depth, unsigned char direction, const name *neighbors[], unsigned char *chunk_index) {\
    if (node != NULL) {\
        if (direction == direction_left) {\
            if (node_position.x != 0) return &node->nodes[node_index_with_left[node_index]];\
        } else if (direction == direction_right) {\
            if (node_position.x != 1) return &node->nodes[node_index_with_right[node_index]];\
        } else if (direction == direction_down) {\
            if (node_position.y != 0) return &node->nodes[node_index_with_down[node_index]];\
        } else if (direction == direction_up) {\
            if (node_position.y != 1) return &node->nodes[node_index_with_up[node_index]];\
        } else if (direction == direction_back) {\
            if (node_position.z != 0) return &node->nodes[node_index_with_back[node_index]];\
        } else if (direction == direction_front) {\
            if (node_position.z != 1) return &node->nodes[node_index_with_front[node_index]];\
        }\
    }\
    return find_root_adjacent##_##name(root, position, depth, direction, neighbors, chunk_index);\
}\
\
void on_destroyed##_##name(ecs_iter_t *it) {\
    name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        name *component = &components[i];\
        close_##name(component);\
    }\
}\
\
ECS_CTOR(name, ptr, {\
    /*zoxel_log(" > creating chunk [%s]\n", ptr->nodes == NULL ? "closed nodes" : "open nodes");*/\
    ptr->nodes = NULL;\
    ptr->value = default_value;\
})\
ECS_DTOR(name, ptr, {\
    /*zoxel_log(" > destroying chunk [%s]\n", ptr->nodes == NULL ? "closed nodes" : "open nodes");*/\
    close_##name(ptr);\
})\
ECS_COPY(name, dst, src, {\
    /*zoxel_log(" > copying chunk [%s]\n", dst->nodes == NULL ? "closed nodes" : "open nodes");*/\
    close_##name(dst);\
    clone_##name(dst, src);\
})\
ECS_MOVE(name, dst, src, {\
    /*zoxel_log(" > moving chunk [%s]\n", dst->nodes == NULL ? "closed nodes" : "open nodes");*/\
    dst->nodes = src->nodes;\
    src->nodes = NULL;\
    dst->value = src->value;\
    src->value = default_value;\
})
