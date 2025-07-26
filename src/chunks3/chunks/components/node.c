// used to link static chunk voxel to a entity in world
typedef struct {
    ecs_entity_t value;
} NodeEntityLink;

const byte nodes_w_safety_checks = 1;
const byte nodes_r_safety_checks = 0;

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
    pthread_rwlock_t lock;\
}; zox_custom_component(name)\
\
static inline void write_lock_node(const name *node) {\
    if (nodes_w_safety_checks) {\
        pthread_rwlock_wrlock((pthread_rwlock_t*) &node->lock);\
    }\
}\
\
static inline void write_unlock_node(const name *node) {\
    if (nodes_w_safety_checks) {\
        pthread_rwlock_unlock((pthread_rwlock_t*) &node->lock);\
    }\
}\
\
static inline void read_lock_node(const name *node) {\
    if (nodes_r_safety_checks) {\
        pthread_rwlock_rdlock((pthread_rwlock_t*) &node->lock);\
    }\
}\
\
static inline void read_unlock_node(const name *node) {\
    if (nodes_r_safety_checks) {\
        pthread_rwlock_unlock((pthread_rwlock_t*) &node->lock);\
    }\
}\
\
static inline name* get_children_unlocked_##name(const name *node) {\
    return (name*) node->ptr;\
}\
\
static inline byte is_linked_unlocked##name(const name *node) {\
    return node->type == node_type_instance;\
}\
\
const ecs_entity_t get_node_entity_unlocked_##name(const name *node) {\
    return is_linked_unlocked##name(node) ? ((NodeEntityLink*) node->ptr)->value : 0;\
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
    read_lock_node(node);\
    name* children = (name*) node->ptr;\
    read_unlock_node(node);\
    return children;\
}\
\
static inline ecs_entity_t get_entity_##name(const name *node) {\
    read_lock_node(node);\
    const ecs_entity_t e = ((NodeEntityLink*) node->ptr)->value;\
    read_unlock_node(node);\
    return e;\
}\
\
static inline byte has_children_##name(const name *node) {\
    read_lock_node(node);\
    const byte has_children = node->ptr && node->type == node_type_children;\
    read_unlock_node(node);\
    return has_children;\
}\
\
static inline byte is_linked_##name(const name *node) {\
    read_lock_node(node);\
    const byte linked = node->type == node_type_instance;\
    read_unlock_node(node);\
    return linked;\
}\
\
const ecs_entity_t get_node_entity_##name(const name *node) {\
    read_lock_node(node);\
    const ecs_entity_t e = is_linked_unlocked##name(node) ? ((NodeEntityLink*) node->ptr)->value : 0;\
    read_unlock_node(node);\
    return e;\
}\
\
void link_node_##name(name *node, const ecs_entity_t e) {\
    write_lock_node(node);\
    if (node->type == node_type_closed) {\
        node->type = node_type_instance;\
        node->ptr = malloc(sizeof(NodeEntityLink));\
        *(NodeEntityLink*) node->ptr = (NodeEntityLink) { e };\
    }\
    write_unlock_node(node);\
}\
\
void destroy_##name(ecs_world_t *world, name* node);\
\
void destroy_node_children_##name(ecs_world_t *world, name *node) {\
    write_lock_node(node);\
    name* kids = get_children_unlocked_##name(node);\
    for (byte i = 0; i < octree_length; i++) {\
        destroy_##name(world, &kids[i]);\
    }\
    free(node->ptr);\
    node->type = node_type_closed;\
    node->ptr = NULL;\
    write_unlock_node(node);\
}\
\
byte destroy_node_entity_##name(ecs_world_t *world, name *node) {\
    write_lock_node(node);\
    byte did_destroy = 0;\
    if (is_linked_##name(node)) {\
        const ecs_entity_t e = get_node_entity_unlocked_##name(node);\
        if (zox_valid(e)) {\
            zox_delete(e)\
            did_destroy = 1;\
        }\
        free(node->ptr);\
        node->ptr = NULL;\
        node->type = node_type_closed;\
    }\
    write_unlock_node(node);\
    return did_destroy;\
}\
\
void destroy_##name(ecs_world_t *world, name* node) {\
    if (!is_closed_##name(node)) {\
        if (is_linked_##name(node)) {\
            destroy_node_entity_##name(world, node);\
        } else {\
            destroy_node_children_##name(world, node);\
        }\
    }\
    pthread_rwlock_destroy(&node->lock);\
}\
\
ECS_DTOR(name, ptr, {\
    destroy_##name(local_world, ptr);\
})\
\
void create_##name(name* node) {\
    node->ptr = NULL;\
    node->value = default_value;\
    node->type = 0;\
    pthread_rwlock_init(&node->lock, NULL);\
}\
\
ECS_CTOR(name, ptr, {\
    create_##name(ptr);\
})\
\
void open_new_##name(name* node) {\
    write_lock_node(node);\
    node->ptr = malloc(sizeof(name) * octree_length);\
    node->type = node_type_children;\
    name* kids = get_children_unlocked_##name(node);\
    for (byte i = 0; i < octree_length; i++) {\
        create_##name(&kids[i]);\
    }\
    write_unlock_node(node);\
}\
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
        open_new_##name(dst);\
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
    write_lock_node(dst);\
    dst->ptr = src->ptr;\
    dst->value = src->value;\
    dst->type = src->type;\
    write_unlock_node(dst);\
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

