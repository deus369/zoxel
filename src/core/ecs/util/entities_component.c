
#define zox_memory_component_non_dtor(name, type)\
typedef struct {\
    int length;\
    type *value;\
} name; zox_custom_component(name);\
\
void zero##_##name(name *ptr) {\
    ptr->length = 0;\
    ptr->value = NULL;\
}\
\
void dispose2##_##name(name *ptr) {\
    if (!ptr->length) return;\
    free(ptr->value);\
    zero##_##name(ptr);\
}\
\
ECS_CTOR(name, ptr, { zero##_##name(ptr); })\
ECS_MOVE(name, dst, src, {\
    if (dst->value == src->value) return;\
    dispose2##_##name(dst);\
    dst->value = src->value;\
    dst->length = src->length;\
    zero##_##name(src);\
})\
ECS_COPY(name, dst, src, {\
    if (src->value) {\
        if (dst->length) free(dst->value);\
        int memory_length = src->length * sizeof(type);\
        dst->length = src->length;\
        dst->value = malloc(memory_length);\
        if (dst->value != NULL) dst->value = memcpy(dst->value, src->value, memory_length);\
    } else if (dst->value) {\
        dispose2##_##name(dst);\
    }\
})

#define zox_define_memory_component_non_dtor(name)\
zox_define_component(name)\
ecs_set_hooks(world, name, {\
    .ctor = ecs_ctor(name),\
    .move = ecs_move(name),\
    .copy = ecs_copy(name),\
});

#define zox_entities_component(name)\
zox_memory_component_non_dtor(name, ecs_entity_t)\
\
void dispose##_##name(ecs_world_t *world, name *ptr) {\
    if (!ptr->length) return;\
    /* using global world atm, no way to push world in from ECS_DTOR.. */\
    for (int j = 0; j < ptr->length; j++) zox_delete(ptr->value[j]);\
    free(ptr->value);\
    ptr->length = 0;\
    ptr->value = NULL;\
}\
\
/*ECS_DTOR(name, ptr, { dispose##_##name(ptr); })*/\
\
void on_destroyed##_##name(ecs_iter_t *it) {\
    ecs_world_t *world = it->world;\
    name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        name *component = &components[i];\
        dispose##_##name(world, component);\
    }\
}

#define zox_define_entities_component2(name, ...)\
/*zox_define_memory_component_non_dtor(name)*/\
\
zox_define_component(name)\
ecs_set_hooks(world, name, {\
    .ctor = ecs_ctor(name),\
    .move = ecs_move(name),\
    .copy = ecs_copy(name),\
    /*.dtor = ecs_dtor(name)*/\
});\
\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

#define zox_define_entities_component(name) zox_define_entities_component2(name, [out] name)

/*
    if (!component->length) continue;\
    for (int j = 0; j < component->length; j++) zox_delete(component->value[j]);\
    free(component->value);\
    component->length = 0;\
    component->value = NULL;\
*/

/*extern int characters_count;

#define zox_entities_component_debug(name)\
zox_memory_component_non_dtor(name, ecs_entity_t)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    ecs_world_t *world = it->world;\
    name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        name *component = &components[i];\
        if (!component->length) continue;\
        zoxel_log(" - destroying entities (characters) [%i]\n", component->length);\
        for (int j = 0; j < component->length; j++) zoxel_log("     - character [%lu]\n", component->value[j]);\
        for (int j = 0; j < component->length; j++) {\
            zox_delete(component->value[j]);\
            characters_count--;\
        }\
        free(component->value);\
        component->length = 0;\
        component->value = NULL;\
    }\
}*/

// const
// zoxel_log(" > destroying components [%i]\n", it->count);
// zoxel_log("     > destroying [%i] data [%i]\n", i, component->length);