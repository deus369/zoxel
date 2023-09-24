
#define zox_memory_component_non_dtor(name, type)\
typedef struct {\
    int length;\
    type *value;\
} name; ECS_COMPONENT_DECLARE(name);\
\
ECS_CTOR(name, ptr, {\
    ptr->length = 0;\
    ptr->value = NULL;\
})\
\
ECS_MOVE(name, dst, src, {\
    if (dst->length != 0) free(dst->value);\
    dst->value = src->value;\
    dst->length = src->length;\
    src->value = NULL;\
    src->length = 0;\
})\
\
ECS_COPY(name, dst, src, {\
    if (src->value) {\
        if (dst->length != 0) free(dst->value);\
        int memory_length = src->length * sizeof(type);\
        dst->length = src->length;\
        dst->value = malloc(memory_length);\
        if (dst->value != NULL) dst->value = memcpy(dst->value, src->value, memory_length);\
    }\
})

#define zox_define_memory_component_non_dtor(name)\
    ECS_COMPONENT_DEFINE(world, name);\
    ecs_set_hooks(world, name, {\
        .ctor = ecs_ctor(name),\
        .move = ecs_move(name),\
        .copy = ecs_copy(name),\
    });

#define zox_entities_component(name)\
zox_memory_component_non_dtor(name, ecs_entity_t)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    ecs_world_t *world = it->world;\
    name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        name *component = &components[i];\
        if (!component->length) continue;\
        for (int j = 0; j < component->length; j++) zox_delete(component->value[j]);\
        free(component->value);\
        component->length = 0;\
        component->value = NULL;\
    }\
}

extern int characters_count;

#define zox_entities_component_debug(name)\
zox_memory_component_non_dtor(name, ecs_entity_t)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    ecs_world_t *world = it->world;\
    name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        name *component = &components[i];\
        if (!component->length) continue;\
        /*zoxel_log(" - destroying entities (characters) [%i]\n", component->length);*/\
        /*for (int j = 0; j < component->length; j++) zoxel_log("     - character [%lu]\n", component->value[j]);*/\
        for (int j = 0; j < component->length; j++) {\
            zox_delete(component->value[j]);\
            characters_count--;\
        }\
        free(component->value);\
        component->length = 0;\
        component->value = NULL;\
    }\
}

// const
// zoxel_log(" > destroying components [%i]\n", it->count);
// zoxel_log("     > destroying [%i] data [%i]\n", i, component->length);

#define zox_define_entities_component2(name, ...)\
zox_define_memory_component_non_dtor(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

#define zox_define_entities_component(name) zox_define_entities_component2(name, [out] name)
