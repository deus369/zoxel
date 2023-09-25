#define zox_entities_component(name)\
zox_memory_component(name, ecs_entity_t)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    ecs_world_t *world = it->world;\
    const name *components = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        const name *component = &components[i];\
        if (!component->value) continue;\
        for (int j = 0; j < component->length; j++) zox_delete(component->value[j]);\
    }\
}

#define zox_define_entities_component2(name, ...)\
zox_define_memory_component(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

#define zox_define_entities_component(name) zox_define_entities_component2(name, [in] name)