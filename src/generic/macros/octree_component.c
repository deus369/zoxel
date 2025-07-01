// used to link static chunk voxel to a entity in world
typedef struct {
    ecs_entity_t value;
} NodeEntityLink;

#define linked_state 255

// todo: Seperate: voxel octree shoudl be seperate to entity component

#define zoxel_octree_component(name, type, default_value)\
\
typedef struct name name;\
\
struct name {\
    type value;\
    name *nodes;\
    byte linked;\
}; ECS_COMPONENT_DECLARE(name);\
\
byte is_linking_##name(const name *node) {\
    return node && node->linked == linked_state;\
}\
\
void link_node_##name(name *node, const ecs_entity_t e) {\
    if (!node || node->nodes || node->linked == linked_state) {\
        return;\
    }\
    node->linked = linked_state;\
    node->nodes = malloc(sizeof(NodeEntityLink));\
    *(NodeEntityLink*) node->nodes = (NodeEntityLink) { e };\
}\
\
byte unlink_node_##name(ecs_world_t *world, name *node) {\
    if (!node || node->linked != linked_state || !node->nodes) {\
        return 0;\
    }\
    NodeEntityLink *link = (NodeEntityLink*) node->nodes;\
    if (zox_valid(link->value)) {\
        zox_delete(link->value)\
    }\
    free(node->nodes);\
    node->nodes = NULL;\
    node->linked = 0;\
    return 1;\
}\
\
byte delete_node_entity_from_##name(ecs_world_t *world, name *node) {\
    if (!node || !node->nodes) {\
        return 0;\
    }\
    if (node->linked != linked_state) {\
        return 0;\
    }\
    NodeEntityLink *node_entity_link = (NodeEntityLink*) node->nodes;\
    if (!node_entity_link) {\
        return 0;\
    }\
    const ecs_entity_t e = node_entity_link->value;\
    if (zox_valid(e)) {\
        zox_delete(e)\
    }\
    unlink_node_##name(world, node);\
    return 1;\
}\
\
void close_##name(ecs_world_t *world, name* node, byte depth) {\
    if (!node->nodes) {\
        return;\
    }\
    if (delete_node_entity_from_##name(world, node)) {\
        return;\
    }\
    /* > todo: check if entity link here, using depth check */\
    if (depth) {\
        depth--;\
        for (byte i = 0; i < octree_length; i++) {\
            close_##name(world, &node->nodes[i], depth);\
        }\
    }\
    free(node->nodes);\
    node->nodes = NULL;\
    node_memory -= 1;\
    /*zox_log(" > freeing node [%i]\n", (sizeof(name) * octree_length))*/\
}\
\
void open_new_##name(name* node) {\
    /*zox_log(" > opening node [%i + 1 = %i :: %i]\n", sizeof(name*), sizeof(name), (sizeof(name) * octree_length))*/\
    node->nodes = malloc(sizeof(name) * octree_length);\
    for (byte i = 0; i < octree_length; i++) {\
        node->nodes[i] = (name) {\
            .nodes = NULL,\
            .linked = 0,\
        };\
    }\
    node_memory += 1;\
}\
\
void clone_##name(name* dst, const name* src) {\
    dst->value = src->value;\
    dst->linked = src->linked;\
    if (src->linked) {\
        dst->nodes = src->nodes;\
    } else if (src->nodes) {\
        open_new_##name(dst);\
        for (byte i = 0; i < octree_length; i++) {\
            clone_##name(&dst->nodes[i], &src->nodes[i]);\
        }\
    } else {\
        dst->nodes = NULL;\
    }\
}\
\
void clone_depth_##name(name* dst, const name* src, const byte max_depth, byte depth) {\
    dst->value = src->value;\
    dst->linked = src->linked;\
    depth++;\
    if (src->nodes && depth <= max_depth) {\
        open_new_##name(dst);\
        for (byte i = 0; i < octree_length; i++) {\
            clone_depth_##name(&dst->nodes[i], &src->nodes[i], max_depth, depth);\
        }\
    } else {\
        dst->nodes = src->nodes;\
        /*dst->nodes = NULL;*/\
    }\
}\
\
void clone_at_depth_##name(name* dst, const name* src, const byte target_depth, byte depth) {\
    if (target_depth > 0 && depth == target_depth - 1) {\
        if (src->nodes) {\
            open_new_##name(dst);\
        }\
    }\
    if (depth == target_depth) {\
        dst->value = src->value;\
        dst->nodes = src->nodes;\
        dst->linked = src->linked;\
    } else {\
        if (src->nodes && dst->nodes) {\
            depth++;\
            for (byte i = 0; i < octree_length; i++) {\
                clone_at_depth_##name(&dst->nodes[i], &src->nodes[i], target_depth, depth);\
            }\
        }\
    }\
}\
\
void open_##name(name* node) {\
    if (node->nodes == NULL) {\
        open_new_##name(node);\
    }\
}\
\
const type find_node_value_##name(const name* node, int3 position, byte depth) {\
    /* if depth finish or if closed node, return node early */ \
    if (!node) {\
        return 0;\
    }\
    if (depth == 0 || node->nodes == NULL) {\
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
    return find_node_value_##name(&node->nodes[int3_to_node_index(local_position)], child_octree_position, depth);\
}\
\
const name* find_node_##name(const name* node, int3 position, byte depth) {\
    /* if depth finish or if closed node, return node early */ \
    if (node == NULL) {\
        return NULL;\
    }\
    if (depth == 0 || node->nodes == NULL) {\
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
    return find_node_##name(&node->nodes[int3_to_node_index(local_position)], child_octree_position, depth);\
}\
\
/* maybe make below function use this if it isn't in the non root node */\
const name* find_root_adjacent_##name(const name* root, int3 position, byte depth, byte direction, const name *neighbors[], byte *chunk_index) {\
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
        /* special case for adjacent nodes, flips position and crosses to neighbor chunk */\
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
const name* find_adjacent_##name(const name* root, const name* node, int3 position, byte node_index, byte3 node_position,\
    byte depth, byte direction, const name *neighbors[], byte *chunk_index) {\
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
    if (root != NULL) {\
        return find_root_adjacent_##name(root, position, depth, direction, neighbors, chunk_index);\
    }\
    return NULL;\
}\
\
ECS_CTOR(name, ptr, {\
    /*zox_log(" > creating chunk [%s]\n", ptr->nodes == NULL ? "closed nodes" : "open nodes")*/\
    ptr->nodes = NULL;\
    ptr->value = default_value;\
    ptr->linked = 0;\
})\
\
ECS_COPY(name, dst, src, {\
    /*zox_log(" > copying chunk [%s]\n", dst->nodes == NULL ? "closed nodes" : "open nodes")*/\
    /* shouldn't i just set pointersh ere?? */\
    /*dst->linked = src->linked;*/\
    clone_##name(dst, src);\
    /*close_##name(dst, dst->max_depth);*/\
})\
\
ECS_MOVE(name, dst, src, {\
    /*zox_log(" > moving chunk [%s]\n", dst->nodes == NULL ? "closed nodes" : "open nodes")*/\
    dst->nodes = src->nodes;\
    src->nodes = NULL;\
    dst->value = src->value;\
    src->value = default_value;\
    dst->linked = src->linked;\
    src->linked = 0;\
})\
\
void on_destroyed_##name(ecs_iter_t *it) {\
    name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        name *component = &components[i];\
        close_##name(it->world, component, component->linked);\
    }\
}\

#define zox_define_component_octree(name)\
    zox_define_component(name)\
    ecs_set_hooks(world, name, {\
        .ctor = ecs_ctor(name),\
        .move = ecs_move(name),\
        .copy = ecs_copy(name),\
    });\
    ecs_observer_init(world, &(ecs_observer_desc_t) {\
        .filter.expr = "[out] "#name,\
        .callback = on_destroyed_##name,\
        .events = { EcsOnRemove },\
    });
