// a copy of zox_indicies_component in order to track triangles_count
int triangles_count = 0;

#define zox_indicies_component(name, type)\
typedef struct {\
    int length;\
    type *value;\
} name; zox_custom_component(name)\
void zero##_##name(name *ptr) {\
    ptr->value = NULL;\
    ptr->length = 0;\
}\
void dispose##_##name(name *ptr) {\
    if (!ptr->value) return;\
    triangles_count -= ptr->length / 3;\
    free(ptr->value);\
    zero##_##name(ptr);\
    memorys_allocated--;\
}\
ECS_CTOR(name, ptr, { zero##_##name(ptr); })\
ECS_DTOR(name, ptr, { dispose##_##name(ptr); })\
ECS_MOVE(name, dst, src, {\
    if (dst->value == src->value) return;\
    dispose##_##name(dst);\
    dst->length = src->length;\
    dst->value = src->value;\
    zero##_##name(src);\
})\
ECS_COPY(name, dst, src, {\
    if (!src->value) {\
        dispose##_##name(dst);\
    } else {\
        int memory_length = src->length * sizeof(type);\
        if (dst->value) dispose##_##name(dst);\
        dst->length = src->length;\
        dst->value = memcpy(malloc(memory_length), src->value, memory_length);\
        memorys_allocated++;\
        triangles_count += src->length / 3;\
    }\
})\

#define zox_define_indicies_component2(name, ...)\
zox_define_component(name)\
ecs_set_hooks(world, name, {\
    .ctor = ecs_ctor(name),\
    .move = ecs_move(name),\
    .copy = ecs_copy(name),\
    .dtor = ecs_dtor(name)\
});

#define zox_define_indicies_component(name) zox_define_indicies_component2(name, [out] name)

#define clear_indicies_component(component) {\
    if (component->value) {\
        triangles_count -= component->length / 3;\
        free(component->value);\
        component->value = NULL;\
        component->length = 0;\
        memorys_allocated--;\
        /*zox_logg("      memorys decreased (clear_memory)\n")*/\
    }\
}
