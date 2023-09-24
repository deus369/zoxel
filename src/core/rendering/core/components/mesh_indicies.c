/*
#define zoxel_memory_component_mesh_indicies(name, type)\
typedef struct {\
    int length;\
    type *value;\
} name; ECS_COMPONENT_DECLARE(name);\
\
ECS_CTOR(name, ptr, {\
    ptr->length = 0;\
    ptr->value = NULL;\
})\
ECS_DTOR(MeshIndicies, ptr, {\
    if (ptr->value) free(ptr->value);\
})\
ECS_MOVE(name, dst, src, {\
    if (dst->length != 0) free(dst->value);\
    dst->value = src->value;\
    dst->length = src->length;\
    src->value = NULL;\
    src->length = 0;\
})\
ECS_COPY(name, dst, src, {\
    if (src->value) {\
        if (dst->length != 0) free(dst->value);\
        int memory_length = src->length * sizeof(type);\
        dst->length = src->length;\
        dst->value = malloc(memory_length);\
        if (dst->value != NULL) dst->value = memcpy(dst->value, src->value, memory_length);\
    }\
})

// define mesh indicies with custom destruction function
zoxel_memory_component_mesh_indicies(MeshIndicies, int)
*/