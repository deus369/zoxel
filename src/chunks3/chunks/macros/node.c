#define zox_component_node(name, base, default_value)\
typedef struct name name;\
struct name {\
    base value;\
    byte type;\
    void* ptr;\
    zox_lock lock;\
}; zox_custom_component(name)\
\
zox_hookr(on_destroyed_##name, byte, (ecs_world_t* world, name* node), (world, node));\
\
void destroy_##name(ecs_world_t *world, name* node);\
\
void* get_new_children_##name() {\
    return (void*) malloc(sizeof(name) * octree_length);\
}\
\
static inline void create_lock_##name(name *node) {\
    if (nodes_w_safety_locks || nodes_r_safety_locks) {\
        zox_lock_init(&node->lock);\
    }\
}\
\
static inline void destroy_lock_##name(name *node) {\
    if (nodes_w_safety_locks || nodes_r_safety_locks) {\
        zox_lock_destroy(&node->lock);\
    }\
}\
\
static inline void write_lock_##name(const name *node) {\
    if (nodes_w_safety_locks) {\
        zox_lock_write(&node->lock);\
    }\
}\
\
static inline void write_unlock_##name(const name *node) {\
    if (nodes_w_safety_locks) {\
        zox_unlock_write(&node->lock);\
    }\
}\
\
static inline void read_lock_##name(const name *node) {\
    if (nodes_r_safety_locks) {\
        zox_lock_read(&node->lock);\
    }\
}\
\
static inline void read_unlock_##name(const name *node) {\
    if (nodes_r_safety_locks) {\
        zox_unlock_read(&node->lock);\
    }\
}\
\
static inline name* get_children_unlocked_##name(const name *node) {\
    return (name*) node->ptr;\
}\
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
    name* children = node ? (name*) node->ptr : NULL;\
    return children;\
}\
\
static inline byte has_children_##name(const name *node) {\
    return node && node->type == node_type_children && node->ptr;\
}\
\
void create_##name(name* node) {\
    node->ptr = NULL;\
    node->value = default_value;\
    node->type = 0;\
    create_lock_##name(node);\
}\
\
void open_##name(name* node) { \
    /*write_lock_##name(node);*/ \
    node->ptr = get_new_children_##name(); \
    if (node->ptr) { \
        node->type = node_type_children; \
        name* kids = get_children_unlocked_##name(node); \
        for (byte i = 0; i < octree_length; i++) { \
            create_##name(&kids[i]); \
        } \
    } \
    /*write_unlock_##name(node);*/ \
}\
\
void close_##name(ecs_world_t *world, name *node) {\
    if (!has_children_##name(node)) { \
        return; \
    } \
    name* kids = get_children_unlocked_##name(node); \
    for (byte i = 0; i < octree_length; i++) { \
        destroy_##name(world, &kids[i]); \
    } \
    free(node->ptr); \
    node->type = node_type_closed; \
    node->ptr = NULL; \
}\
\
void destroy_##name(ecs_world_t *world, name* node) {\
    if (!is_closed_##name(node)) {\
        if (has_children_##name(node)) {\
            close_##name(world, node);\
        } else {\
            run_hook_on_destroyed_##name(world, node);\
        }\
    }\
    destroy_lock_##name(node);\
}\
\
ECS_DTOR(name, ptr, {\
    destroy_##name(local_world, ptr);\
})\
\
ECS_CTOR(name, ptr, {\
    create_##name(ptr);\
})\
\
void clone_tree_##name(\
    name* dst,\
    const name* src)\
{\
    dst->value = src->value;\
    dst->type = src->type;\
    if (src->type == node_type_instance) {\
        dst->ptr = src->ptr;\
    } else if (src->ptr) {\
        open_##name(dst);\
        name* kids_dst = get_children_##name(dst);\
        name* kids_src = get_children_##name(src);\
        for (byte i = 0; i < octree_length; i++) {\
            clone_tree_##name(&kids_dst[i], &kids_src[i]);\
        }\
    } else {\
        dst->ptr = NULL;\
    }\
}\
\
ECS_COPY(name, dst, src, {\
    clone_tree_##name(dst, src);\
})\
\
ECS_MOVE(name, dst, src, {\
    /*write_lock_##name(dst);*/\
    dst->ptr = src->ptr;\
    dst->value = src->value;\
    dst->type = src->type;\
    /*write_unlock_##name(dst);*/\
    src->ptr = NULL;\
    src->value = default_value;\
    src->type = 0;\
})\
\
void dispose_system_##name(ecs_iter_t *it) {\
    zox_sys_world()\
    zox_sys_begin()\
    zox_sys_out(name)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_o(name, component)\
        destroy_##name(world, component);\
    }\
}

#define zox_define_component_node(name)\
    zox_define_component(name)\
    ecs_set_hooks(world, name, {\
        .ctor = ecs_ctor(name),\
        .move = ecs_move(name),\
        .copy = ecs_copy(name),\
        .dtor = ecs_dtor(name),\
    });\
    zox_observe_expr(dispose_system_##name, EcsOnRemove, "[out] "#name)

