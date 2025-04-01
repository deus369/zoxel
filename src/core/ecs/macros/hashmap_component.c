#define zox_hashmap_component(name, type)\
zox_component(name, type##_##hashmap*)\
\
void dispose_##type##_hashmap(ecs_world_t *world, type##_##hashmap* hashmap) {\
    ecs_entity_t_array_d* entities = create_ecs_entity_t_array_d(initial_dynamic_array_size);\
    for (int j = 0; j < hashmap->size; j++) {\
        type##_##hashmap_pair *pair = hashmap->data[j];\
        while (pair != NULL) {\
            const ecs_entity_t e = pair->value;\
            if (zox_valid(e)) {\
                /*zox_delete(e)*/\
                add_to_ecs_entity_t_array_d(entities, e);\
            }\
            pair = pair->next;\
        }\
    }\
    type##_##hashmap_dispose(hashmap);\
    for (int i = 0; i < entities->size; i++) {\
        const ecs_entity_t e = entities->data[i];\
        /*zox_log("- deleting terrain_chunk %lu\n", e)*/\
        /*zox_geter(e, EntityLinks, entityLinks)*/\
        /*zox_log("!!! disposing entity links chunk [%lu] %i\n", e, entityLinks->length)*/\
        zox_delete(e)\
    }\
    dispose_ecs_entity_t_array_d(entities);\
}\
\
void on_destroyed##_##name(ecs_iter_t *it) {\
    zox_field_world()\
    zox_field_out(name, components, 1)\
    for (int i = 0; i < it->count; i++) {\
        zox_field_o(name, components, component)\
        if (!component->value) continue;\
        type##_##hashmap* hashmap = component->value;\
        component->value = NULL;\
        dispose_##type##_hashmap(world, hashmap);\
    }\
}

#define zox_define_hashmap_component2(name, ...)\
zox_define_component(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

#define zox_define_hashmap_component(name) zox_define_hashmap_component2(name, [out] name)
