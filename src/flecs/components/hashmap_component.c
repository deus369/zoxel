#define zox_hashmap_component(name, type)\
zox_component(name, type##_hashmap*)\
\
void dispose_hashmap_##type(ecs_world_t *world, type##_hashmap* hashmap) {\
    for (int j = 0; j < hashmap->size; j++) {\
        type##_hashmap_pair *pair = hashmap->data[j];\
        while (pair) {\
            const ecs_entity_t e = pair->value;\
            if (zox_valid(e)) {\
                zox_delete(e)\
            }\
            pair = pair->next;\
        }\
    }\
    type##_##hashmap_dispose(hashmap);\
}\
\
void on_destroyed_##name(ecs_iter_t *it) {\
    zox_sys_world()\
    zox_sys_begin()\
    zox_sys_out(name)\
    for (int i = 0; i < it->count; i++) {\
        zox_sys_o(name, component)\
        if (!component->value) {\
            continue;\
        }\
        type##_hashmap* hashmap = component->value;\
        dispose_hashmap_##type(world, hashmap);\
        component->value = NULL;\
    }\
}

#define zox_define_hashmap_component2(name, ...)\
    zox_define_component(name)\
    zox_observe(on_destroyed_##name, EcsOnRemove, __VA_ARGS__)

#define zox_define_hashmap_component(name)\
    zox_define_hashmap_component2(name, [out] name)
