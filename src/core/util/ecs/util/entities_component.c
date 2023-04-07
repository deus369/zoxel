#define zoxel_entities_component_define(world, ComponentName) {\
    ECS_COMPONENT_DEFINE(world, ComponentName);\
    ecs_set_hooks(world, ComponentName, {\
        .ctor = ecs_ctor(ComponentName),\
        .move = ecs_move(ComponentName),\
        .copy = ecs_copy(ComponentName),\
        .dtor = ecs_dtor(ComponentName),\
        .ctx = world\
    });\
}

#define zoxel_entities_component(name, type)\
typedef struct {\
    int length;\
    type *value;\
} name;\
ECS_COMPONENT_DECLARE(name);\
ECS_CTOR(name, ptr, {\
    ptr->length = 0;\
    ptr->value = NULL;\
})\
ECS_MOVE(name, dst, src, {\
    if (dst->length != 0) {\
        free(dst->value);\
    }\
    dst->value = src->value;\
    src->value = NULL;\
    dst->length = src->length;\
    src->length = 0;\
})\
ECS_COPY(name, dst, src, {\
    if (src->value) {\
        if (dst->length != 0) {\
            free(dst->value);\
        }\
        int memory_length = src->length * sizeof(type);\
        dst->length = src->length;\
        dst->value = malloc(memory_length);\
        if (dst->value != NULL) {\
            dst->value = memcpy(dst->value, src->value, memory_length);\
        }\
    }\
})\
void name##_##dtor(void *ptr, int32_t count, const ecs_type_info_t *ti) {\
    ecs_world_t *world = ti->hooks.ctx;\
    name *data = ptr;\
    printf("=== dtor children [%i] ===\n", count);\
    for (int i = 0; i < count; i++) {\
        name *ptr2 = &data[i];\
        if (ptr2->value) {\
            printf("    - del children [%i]\n", ptr2->length);\
            for (int i = 0; i < ptr2->length; i++) {\
                type child = ptr2->value[i];\
                if (child != 0) {\
                    printf("        - del child [%lu]\n", (long int) child);\
                    ecs_delete(world, child);\
                }\
            }\
            free(ptr2->value);\
        } else {\
            printf("    - FAILED del children [%i]\n", ptr2->length);\
        }\
    }\
    printf("=== end dtor children ===\n");\
}

// ecs_delete(world, ptr2->value[i]);

/*
name##_##delete_hierarchy(world, child);\

void name##_##delete_hierarchy(ecs_world_t *world, ecs_entity_t e)\
{\
    if (ecs_has(world, e, name))\
    {\
        const name *children = ecs_get(world, e, name);\
        printf("        - del children [%i]\n", children->length);\
        for (int i = 0; i < children->length; i++)\
        {\
            name##_##delete_hierarchy(world, children->value[i]);\
            ecs_delete(world, e);\
        }\
    }\
}
*/