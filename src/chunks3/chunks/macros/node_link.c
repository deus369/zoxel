// typedef struct NodeLink NodeLink;

typedef struct {
    entity value;
} NodeLink;


#define zox_node_add_link(name)\
\
static inline byte is_linked_unlocked_##name(const name *node) {\
    return node->type == node_type_instance;\
}\
\
entity get_node_entity_unlocked_##name(const name *node) {\
    return is_linked_unlocked_##name(node) ? ((NodeLink*) node->ptr)->value : 0;\
}\
\
static inline entity get_entity_##name(const name *node) {\
    const entity e = ((NodeLink*) node->ptr)->value;\
    return e;\
}\
\
static inline byte is_linked_##name(const name *node) {\
    const byte linked = node->type == node_type_instance;\
    return linked;\
}\
\
void link_node_##name(name *node, const entity e) {\
    /*write_lock_##name(node);*/\
    if (node->type == node_type_closed) {\
        node->type = node_type_instance;\
        node->ptr = malloc(sizeof(NodeLink));\
        *(NodeLink*) node->ptr = (NodeLink) { e };\
    }\
    /*write_unlock_##name(node);*/\
}\
\
byte destroy_node_link_##name(ecs *world, name *node) {\
    if (!node || !is_linked_##name(node)) {\
        return 0;\
    }\
    /*write_lock_##name(node);*/\
    byte did_destroy = 0;\
    if (is_linked_##name(node)) {\
        const entity e = get_node_entity_unlocked_##name(node);\
        if (zox_valid(e)) {\
            zox_delete(e)\
            did_destroy = 1;\
        }\
        free(node->ptr);\
        node->ptr = NULL;\
        node->type = node_type_closed;\
    }\
    /*write_unlock_##name(node);*/\
    return did_destroy;\
}\
\
entity get_node_entity_##name(const name *node) {\
    const entity e = is_linked_unlocked_##name(node) ? ((NodeLink*) node->ptr)->value : 0;\
    return e;\
}
