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
    pthread_rwlock_t lock;\
}; zox_custom_component(name)\
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
    pthread_rwlock_rdlock((pthread_rwlock_t*)&node->lock);\
    name* children = (name*) node->ptr;\
    pthread_rwlock_unlock((pthread_rwlock_t*)&node->lock);\
    return children;\
}\
\
static inline name* get_children_unlocked_##name(const name *node) {\
    return (name*) node->ptr;\
}\
\
static inline ecs_entity_t get_entity_##name(const name *node) {\
    pthread_rwlock_rdlock((pthread_rwlock_t*)&node->lock);\
    const ecs_entity_t e = ((NodeEntityLink*) node->ptr)->value;\
    pthread_rwlock_unlock((pthread_rwlock_t*)&node->lock);\
    return e;\
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
const ecs_entity_t get_node_entity_##name(const name *node) {\
    pthread_rwlock_rdlock((pthread_rwlock_t*)&node->lock);\
    const ecs_entity_t e = is_linked_##name(node) ? ((NodeEntityLink*) node->ptr)->value : 0;\
    pthread_rwlock_unlock((pthread_rwlock_t*)&node->lock);\
    return e;\
}\
\
void link_node_##name(name *node, const ecs_entity_t e) {\
    pthread_rwlock_wrlock((pthread_rwlock_t*)&node->lock);\
    if (node->type == node_type_closed) {\
        node->type = node_type_instance;\
        node->ptr = malloc(sizeof(NodeEntityLink));\
        *(NodeEntityLink*) node->ptr = (NodeEntityLink) { e };\
    }\
    pthread_rwlock_unlock((pthread_rwlock_t*)&node->lock);\
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
    pthread_rwlock_wrlock(&node->lock);\
    free(node->ptr);\
    node->ptr = NULL;\
    node->type = node_type_closed;\
    pthread_rwlock_unlock(&node->lock);\
    return 1;\
}\
\
void create_##name(name* node) {\
    node->ptr = NULL;\
    node->value = default_value;\
    node->type = 0;\
    pthread_rwlock_init(&node->lock, NULL);\
}\
\
void destroy_##name(ecs_world_t *world, name* node) {\
    if (!is_closed_##name(node)) {\
        if (is_linked_##name(node)) {\
            destroy_node_entity_##name(world, node);\
        } else {\
            pthread_rwlock_wrlock(&node->lock);\
            name* kids = get_children_unlocked_##name(node);\
            for (byte i = 0; i < octree_length; i++) {\
                destroy_##name(world, &kids[i]);\
            }\
            free(node->ptr);\
            node->type = node_type_closed;\
            node->ptr = NULL;\
            pthread_rwlock_unlock(&node->lock);\
        }\
    }\
    pthread_rwlock_destroy(&node->lock);\
}\
\
void open_new_##name(name* node) {\
    pthread_rwlock_wrlock(&node->lock);\
    node->ptr = malloc(sizeof(name) * octree_length);\
    node->type = node_type_children;\
    name* kids = get_children_unlocked_##name(node);\
    for (byte i = 0; i < octree_length; i++) {\
        create_##name(&kids[i]);\
    }\
    pthread_rwlock_unlock(&node->lock);\
}\
\
void clone_##name(\
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
            clone_##name(&kids_dst[i], &kids_src[i]);\
        }\
    } else {\
        dst->ptr = NULL;\
    }\
}\
\
void open_##name(name* node) {\
    if (node->ptr == NULL) {\
        open_new_##name(node);\
    }\
}\
\
ECS_CTOR(name, ptr, {\
    create_##name(ptr);\
})\
\
ECS_COPY(name, dst, src, {\
    pthread_rwlock_init(&dst->lock, NULL);\
    clone_##name(dst, src);\
})\
\
ECS_MOVE(name, dst, src, {\
    pthread_rwlock_init(&dst->lock, NULL);\
    dst->ptr = src->ptr;\
    dst->value = src->value;\
    dst->type = src->type;\
    src->ptr = NULL;\
    src->value = default_value;\
    src->type = 0;\
    pthread_rwlock_destroy(&src->lock);\
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
    });\
    zox_observe_expr(dispose_system_##name, EcsOnRemove, "[out] "#name)

