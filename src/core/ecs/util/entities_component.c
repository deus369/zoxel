#define zox_entities_component(name)\
zox_memory_component(name, ecs_entity_t)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    ecs_world_t *world = it->world;\
    ecs_defer_begin(world);\
    const name *children = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        const name *children2 = &children[i];\
        for (int j = 0; j < children2->length; j++) {\
            zox_delete(children2->value[j]);\
        }\
    }\
    ecs_defer_end(world);\
}

#define zox_define_entities_component(name, ...)\
zox_define_memory_component(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});
