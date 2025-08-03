#define zox_component_node_helper(name, base)\
\
const base find_node_value_##name(\
    const name* node,\
    int3 position,\
    byte depth)\
{\
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
    byte depth)\
{\
    if (!depth || !has_children_##name(node)) {\
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
    return find_node_##name( \
        &kids[int3_to_node_index(local_position)], \
        child_octree_position, depth);\
}\
\
/* maybe make below function use this if it isn't in the non root node */\
const name* find_root_adjacent_##name(\
    const name* root,\
    int3 position,\
    byte depth,\
    byte direction,\
    const name *neighbors[],\
    byte *chunk_index)\
{\
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
    byte *chunk_index)\
{\
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
        /*dst->ptr = src->ptr;*/\
        /*dst->type = src->type;*/\
    } else {\
        if (src->ptr && dst->ptr) {\
            depth++;\
            name* kids_src = get_children_##name(src);\
            name* kids_dst = get_children_##name(dst);\
            for (byte i = 0; i < octree_length; i++) {\
                clone_at_depth_##name(&kids_dst[i], &kids_src[i], target_depth, depth);\
            }\
        }\
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
}
