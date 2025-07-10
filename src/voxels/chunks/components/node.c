// used to link static chunk voxel to a entity in world
typedef struct {
    ecs_entity_t value;
} NodeEntityLink;

#define node_type_closed 0
#define node_type_children 1
#define node_type_instance 255

#define zox_component_node(name, base, default_value)\
\
typedef struct name name;\
struct name {\
    base value;\
    byte type;\
    void* ptr;\
};\
zox_custom_component(name)\
\
static inline byte is_opened_##name(const name *node) {\
    return node->ptr != NULL;\
}\
\
static inline byte is_closed_##name(const name *node) {\
    return node->ptr == NULL;\
}\
\
static inline name* get_children_##name(const name *node) {\
    return (name*) node->ptr;\
}\
\
static inline ecs_entity_t get_entity_##name(const name *node) {\
    return ((NodeEntityLink*) node->ptr)->value;\
}\
\
static inline byte has_children_##name(const name *node) {\
    return node->ptr && node->type == node_type_children;\
}\
\
static inline byte is_linked_##name(const name *node) {\
    return node->type == node_type_instance;\
}\
\
void link_node_##name(name *node, const ecs_entity_t e) {\
    if (node->type != node_type_closed) {\
        return;\
    }\
    node->type = node_type_instance;\
    node->ptr = malloc(sizeof(NodeEntityLink));\
    *(NodeEntityLink*) node->ptr = (NodeEntityLink) { e };\
}\
\
const ecs_entity_t get_node_entity_##name(const name *node) {\
    if (!is_linked_##name(node)) {\
        return 0;\
    } else {\
        NodeEntityLink *link = (NodeEntityLink*) node->ptr;\
        return link->value;\
    }\
}\
\
byte destroy_node_entity_##name(ecs_world_t *world, name *node) {\
    if (!is_linked_##name(node)) {\
        return 0;\
    }\
    const ecs_entity_t e = get_node_entity_##name(node);\
    if (zox_valid(e)) {\
        zox_delete(e)\
    } else {\
        zox_log_error("invalid node entity [%lu]", e)\
    }\
    free(node->ptr);\
    node->ptr = NULL;\
    node->type = node_type_closed;\
    return 1;\
}\
\
void dispose_##name(ecs_world_t *world, name* node) {\
    if (is_closed_##name(node)) {\
        return;\
    } else if (is_linked_##name(node)) {\
        destroy_node_entity_##name(world, node);\
    } else {\
        name* kids = get_children_##name(node);\
        for (byte i = 0; i < octree_length; i++) {\
            dispose_##name(world, &kids[i]);\
        }\
        free(node->ptr);\
        node->type = node_type_closed;\
        node->ptr = NULL;\
    }\
}\
\
void open_new_##name(name* node) {\
    node->ptr = malloc(sizeof(name) * octree_length);\
    node->type = node_type_children;\
    name* kids = get_children_##name(node);\
    for (byte i = 0; i < octree_length; i++) {\
        kids[i] = (name) {\
            .value = default_value,\
            .type = node_type_closed,\
            .ptr = NULL,\
        };\
    }\
}\
\
void clone_##name(name* dst, const name* src) {\
    dst->value = src->value;\
    dst->type = src->type;\
    if (src->type == node_type_instance) {\
        dst->ptr = src->ptr;\
    } else if (src->ptr) {\
        open_new_##name(dst);\
        name* kids_dst = get_children_##name(dst);\
        name* kids_src = get_children_##name(src);\
        for (byte i = 0; i < octree_length; i++) {\
            clone_##name(&kids_dst[i], &kids_src[i]);\
        }\
    } else {\
        dst->ptr = NULL;\
    }\
}\
\
void clone_depth_##name(\
    name* dst,\
    const name* src,\
    const byte max_depth,\
    byte depth) {\
    dst->value = src->value;\
    dst->type = src->type;\
    depth++;\
    if (src->ptr && depth <= max_depth) {\
        open_new_##name(dst);\
        name* kids_dst = get_children_##name(dst);\
        name* kids_src = get_children_##name(src);\
        for (byte i = 0; i < octree_length; i++) {\
            clone_depth_##name(&kids_dst[i], &kids_src[i], max_depth, depth);\
        }\
    } else {\
        dst->ptr = src->ptr;\
        /*dst->ptr = NULL;*/\
    }\
}\
\
void clone_at_depth_##name(\
    name* dst,\
    const name* src,\
    const byte target_depth,\
    byte depth) {\
    if (target_depth > 0 && depth == target_depth - 1) {\
        if (src->ptr) {\
            open_new_##name(dst);\
        }\
    }\
    if (depth == target_depth) {\
        dst->value = src->value;\
        dst->ptr = src->ptr;\
        dst->type = src->type;\
    } else {\
        if (src->ptr && dst->ptr) {\
            depth++;\
            name* kids_dst = get_children_##name(dst);\
            name* kids_src = get_children_##name(src);\
            for (byte i = 0; i < octree_length; i++) {\
                clone_at_depth_##name(&kids_dst[i], &kids_src[i], target_depth, depth);\
            }\
        }\
    }\
}\
\
void open_##name(name* node) {\
    if (node->ptr == NULL) {\
        open_new_##name(node);\
    }\
}\
\
const base find_node_value_##name(\
    const name* node,\
    int3 position,\
    byte depth) {\
    /* if depth finish or if closed node, return node early */ \
    if (depth == 0 || node->ptr == NULL) {\
        return node->value;\
    }\
    depth--;\
    byte dividor = powers_of_two[depth];\
    int3 local_position = (int3) {\
        position.x / dividor,\
        position.y / dividor,\
        position.z / dividor\
    };\
    int3 child_octree_position = (int3) {\
        position.x % dividor,\
        position.y % dividor,\
        position.z % dividor\
    };\
    name* kids = get_children_##name(node);\
    return find_node_value_##name(&kids[int3_to_node_index(local_position)], child_octree_position, depth);\
}\
\
const name* find_node_##name(\
    const name* node,\
    int3 position,\
    byte depth) {\
    if (depth == 0 || node->ptr == NULL) {\
        return node;\
    }\
    depth--;\
    byte dividor = powers_of_two[depth];\
    int3 local_position = (int3) {\
        position.x / dividor,\
        position.y / dividor,\
        position.z / dividor\
    };\
    int3 child_octree_position = (int3) {\
        position.x % dividor,\
        position.y % dividor,\
        position.z % dividor\
    };\
    name* kids = get_children_##name(node);\
    return find_node_##name(&kids[int3_to_node_index(local_position)], child_octree_position, depth);\
}\
\
/* maybe make below function use this if it isn't in the non root node */\
const name* find_root_adjacent_##name(\
    const name* root,\
    int3 position,\
    byte depth,\
    byte direction,\
    const name *neighbors[],\
    byte *chunk_index) {\
    if (root == NULL) {\
        return NULL;\
    }\
    if (direction == direction_left) {\
        position.x--;\
    } else if (direction == direction_right) {\
        position.x++;\
    } else if (direction == direction_down)  {\
        position.y--;\
    } else if (direction == direction_up)  {\
        position.y++;\
    } else if (direction == direction_back)  {\
        position.z--;\
    } else if (direction == direction_front)  {\
        position.z++;\
    }\
    byte position_bounds = powers_of_two[depth];\
    if (position.x >= 0 && position.x < position_bounds && position.y >= 0 && position.y < position_bounds && position.z >= 0 && position.z < position_bounds) {\
        return find_node_##name(root, position, depth);\
    } else {\
        /* special case for adjacent ptr, flips position and crosses to neighbor chunk */\
        *chunk_index = direction + 1;\
        if (direction == direction_left) {\
            if (neighbors[direction] != NULL) {\
                position.x = position_bounds - 1;\
                return find_node_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_right) {\
            if (neighbors[direction] != NULL) {\
                position.x = 0;\
                return find_node_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_down) {\
            if (neighbors[direction] != NULL) {\
                position.y = position_bounds - 1;\
                return find_node_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_up) {\
            if (neighbors[direction] != NULL) {\
                position.y = 0;\
                return find_node_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_back) {\
            if (neighbors[direction] != NULL) {\
                position.z = position_bounds - 1;\
                return find_node_##name(neighbors[direction], position, depth);\
            }\
        } else if (direction == direction_front) {\
            if (neighbors[direction] != NULL) {\
                position.z = 0;\
                return find_node_##name(neighbors[direction], position, depth);\
            }\
        }\
        return NULL;\
    }\
}\
\
const name* find_adjacent_##name(\
    const name* root,\
    const name* node,\
    int3 position,\
    byte node_index,\
    byte3 node_position,\
    byte depth,\
    byte direction,\
    const name *neighbors[],\
    byte *chunk_index) {\
    if (node != NULL) {\
        name* kids = get_children_##name(node);\
        if (direction == direction_left) {\
            if (node_position.x != 0) {\
                return &kids[node_index_with_left[node_index]];\
            }\
        } else if (direction == direction_right) {\
            if (node_position.x != 1) {\
                return &kids[node_index_with_right[node_index]];\
            }\
        } else if (direction == direction_down) {\
            if (node_position.y != 0) {\
                return &kids[node_index_with_down[node_index]];\
            }\
        } else if (direction == direction_up) {\
            if (node_position.y != 1) {\
                return &kids[node_index_with_up[node_index]];\
            }\
        } else if (direction == direction_back) {\
            if (node_position.z != 0) {\
                return &kids[node_index_with_back[node_index]];\
            }\
        } else if (direction == direction_front) {\
            if (node_position.z != 1) {\
                return &kids[node_index_with_front[node_index]];\
            }\
        }\
    }\
    if (root != NULL) {\
        return find_root_adjacent_##name(root, position, depth, direction, neighbors, chunk_index);\
    }\
    return NULL;\
}\
\
ECS_CTOR(name, ptr, {\
    ptr->ptr = NULL;\
    ptr->value = default_value;\
    ptr->type = 0;\
})\
\
ECS_COPY(name, dst, src, {\
    clone_##name(dst, src);\
})\
\
ECS_MOVE(name, dst, src, {\
    dst->ptr = src->ptr;\
    src->ptr = NULL;\
    dst->value = src->value;\
    src->value = default_value;\
    dst->type = src->type;\
    src->type = 0;\
})\
\
void dispose_system_##name(ecs_iter_t *it) {\
    zox_sys_world()\
    zox_sys_begin()\
    zox_sys_out(name)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_o(name, component)\
        dispose_##name(world, component);\
    }\
}

#define zox_define_component_node(name)\
    zox_define_component(name)\
    ecs_set_hooks(world, name, {\
        .ctor = ecs_ctor(name),\
        .move = ecs_move(name),\
        .copy = ecs_copy(name),\
    });\
    zox_observe_expr(dispose_system_##name, EcsOnRemove, "[out] "#name)
