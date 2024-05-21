#define zox_declare_tag(name) ECS_DECLARE(name);

#define zox_custom_component(name) ECS_COMPONENT_DECLARE(name);

#define zox_component(name, type)\
typedef struct {\
    type value;\
} name; zox_custom_component(name)

#define zox_event_type(name, return_type, ...)\
typedef struct {\
    return_type (*value)(__VA_ARGS__);\
} name;

#define zox_function_component(name, return_type, ...)\
typedef struct {\
    return_type (*value)(__VA_ARGS__);\
} name; zox_custom_component(name)

#define zox_define_component(name) ECS_COMPONENT_DEFINE(world, name);

// zox_log("   + component [%lu]\n", ecs_id(name))

#define zox_define_tag(name) ECS_TAG_DEFINE(world, name);

// #define zox_time_component(name) zox_component(name, double)

// #define zox_entity_component(name) zox_component(name, ecs_entity_t)

#define zox_define_component_w_dest(name) zox_define_component(name) ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });

#define zox_define_destruction(name) ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });


// destroy spawned entity when it is removed

#define zox_define_entity_parent_component2(name, ...)\
zox_define_component(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

#define zox_define_entity_parent_component(name) zox_define_entity_parent_component2(name, [out] name)

#define zox_component_type_none 0
#define zox_component_type_byte 1
#define zox_component_type_int 2
#define zox_component_type_int2 3
#define zox_component_type_long_int 4
#define zox_component_type_float 5
#define zox_component_type_float2 6
#define zox_component_type_float3 7
#define zox_component_type_float4 8
#define zox_component_type_float4x4 9
#define zox_component_type_ecs_entity_t 10

#define component_id_list(name)\
ecs_entity_t_array_d* component_ids##_##name;\
void initialize_component_ids##_##name() {\
    component_ids##_##name = create_ecs_entity_t_array_d(initial_dynamic_array_size);\
}\
void dispose_component_ids##_##name() {\
    dispose_ecs_entity_t_array_d(component_ids##_##name);\
}\
unsigned char is_component_type##_##name(ecs_entity_t id) { return is_in_ecs_entity_t_array_d(component_ids##_##name, id);  }

#define zox_debug_component(name)  zox_log(" + component [%s] > [%s]\n", #name, zox_get_name(name))


/*#define component_id_list_array(name)\
ecs_entity_t_array_d* component_ids##_##name;\
void initialize_component_ids##_##name() {\
    component_ids##_##name = create_ecs_entity_t_array_d(initial_dynamic_array_size);\
}\
void dispose_component_ids##_##name() {\
    dispose_ecs_entity_t_array_d(component_ids##_##name);\
}\
unsigned char is_component_type##_##name(ecs_entity_t id) { return is_in_ecs_entity_t_array_d(component_ids##_##name, id);  }*/

/*ecs_set_hooks(world, name, { .dtor = ecs_dtor(name) });*/
/*ECS_DTOR(name, ptr, {\
    if (ptr->value != NULL) type##_##hash_map_dispose(ptr->value);\
});*/

/*if (zox_has(pair->value, EntityLinks)) {\
    const EntityLinks *entityLinks = ecs_get(world, pair->value, EntityLinks);\
    for (int k = 0; k < entityLinks->length; k++) {\
        ecs_entity_t character_entity = entityLinks->value[k];\
        zox_delete(character_entity);\
    }\
}\*/
/* 
    const EntityLinks *entityLinks = ecs_get(world, pair->value, EntityLinks);\
    for (int j = 0; j < entityLinks->length; j++) {\
        ecs_entity_t character_entity = entityLinks->value[j];
        zox_delete(character_entity);\
    }
*/
