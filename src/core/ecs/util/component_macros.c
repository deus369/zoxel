#define zox_define_component(name) ECS_COMPONENT_DEFINE(world, name);

#define zox_define_component_w_dest(name) zox_define_component(name)\
    ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });

#define zox_define_destruction(name) ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });

#define zox_declare_tag(name) ECS_DECLARE(name);

#define zox_define_tag(name) ECS_TAG_DEFINE(world, name);

#define zox_component(name, type)\
typedef struct {\
    type value;\
} name;\
ECS_COMPONENT_DECLARE(name);

#define zox_function_component(name, return_type, ...)\
typedef struct {\
    return_type (*value)(__VA_ARGS__);\
} name;\
ECS_COMPONENT_DECLARE(name);

#define zox_byte_component(name) zox_component(name, unsigned char)

#define zox_time_component(name) zox_component(name, double)

#define zox_entity_component(name) zox_component(name, ecs_entity_t)

#define zox_hashmap_component(name, type)\
zox_component(name, type##_##hash_map*)\
ECS_DTOR(name, ptr, {\
    if (ptr->value != NULL) type##_##hash_map_dispose(ptr->value);\
});\
void on_destroyed##_##name(ecs_iter_t *it) {\
    ecs_world_t *world = it->world;\
    const name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        const name *component = &components[i];\
        for (int j = 0; j < component->value->size; j++) {\
            type##_##hash_map_pair* pair = component->value->data[j];\
            while (pair != NULL) {\
                if (ecs_has(world, pair->value, EntityLinks)) {\
                    const EntityLinks *entityLinks = ecs_get(world, pair->value, EntityLinks);\
                    for (int k = 0; k < entityLinks->length; k++) {\
                        ecs_entity_t character_entity = entityLinks->value[k];\
                        zox_delete(character_entity);\
                    }\
                }\
                zox_delete(pair->value);\
                pair = pair->next;\
            }\
        }\
    }\
}

/* 
    const EntityLinks *entityLinks = ecs_get(world, pair->value, EntityLinks);\
    for (int j = 0; j < entityLinks->length; j++) {\
        ecs_entity_t character_entity = entityLinks->value[j];
        zox_delete(character_entity);\
    }
*/

#define zox_define_hashmap_component(name, ...)\
zox_define_component(name)\
ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

#define zox_custom_component(name) ECS_COMPONENT_DECLARE(name);