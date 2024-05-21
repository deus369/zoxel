
#define zox_hashmap_component(name, type)\
zox_component(name, type##_##hash_map*)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    ecs_world_t *world = it->world;\
    name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        name *component = &components[i];\
        if (component->value) {\
            for (int j = 0; j < component->value->size; j++) {\
                type##_##hash_map_pair *pair = component->value->data[j];\
                while (pair != NULL) {\
                    if (pair->value) zox_delete(pair->value);\
                    pair = pair->next;\
                }\
            }\
            type##_##hash_map_dispose(component->value);\
        }\
    }\
}

// if (!component->value || !component->value->data) continue;
// if (!pair->value || ecs_is_alive(world, pair->value))

#define zox_define_hashmap_component2(name, ...)\
zox_define_component(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

#define zox_define_hashmap_component(name) zox_define_hashmap_component2(name, [out] name)
