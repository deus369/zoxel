

/*#define max_node_blocks 1000000
\
static name pool_##name[max_node_blocks][octree_length];\
static int pool_head_##name = -1;\
static int next_free_##name[max_node_blocks];\
\
byte has_init_children_pool_##name = 0;\
\
static void init_children_pool_##name(void) {\
    if (has_init_children_pool_##name) return;\
        has_init_children_pool_##name = 1;\
        for (int i = 0; i < max_node_blocks - 1; i++) {\
            next_free_##name[i] = i + 1;\
        }\
        next_free_##name[max_node_blocks - 1] = -1;\
        pool_head_##name = 0; \
}\
\
void* get_new_children_##name() {\
    if (pool_head_##name < 0) {\
        zox_log_error("AOWIEJWAE")\
        return NULL;\
    }\
    int idx = pool_head_##name;\
    pool_head_##name = next_free_##name[idx];\
    return &pool_##name[idx][0];\
}\
\
void release_children_##name(name *node) {\
    if (!node) return;\
        ptrdiff_t offset = node - &pool_##name[0][0];\
        int idx = offset / octree_length;\
        next_free_##name[idx] = pool_head_##name;\
        pool_head_##name = idx;\
}
init_children_pool_##name();\*/
