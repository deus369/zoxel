#define octree_length 8
#define octree_node_size 2
#define octree_node_size3 (int3) { 2, 2, 2 }

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
})

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