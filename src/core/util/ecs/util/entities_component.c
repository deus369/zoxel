#define zoxel_entities_component(name)\
zoxel_memory_component(Children, ecs_entity_t)\
void on_destroyed##_##name(ecs_iter_t *it) {\
    const name *children = ecs_field(it, name, 1);\
    for (int i = 0; i < it->count; i++) {\
        const name *children2 = &children[i];\
        for (int j = 0; j < children2->length; j++) {\
            ecs_delete(it->world, children2->value[j]);\
        }\
    }\
}

#define zoxel_define_entities_component(name, ...)\
zoxel_define_memory_component(name)\
ecs_observer_init(world, &(ecs_observer_desc_t) {\
    .filter.expr = #__VA_ARGS__,\
    .callback = on_destroyed##_##name,\
    .events = { EcsOnRemove },\
});

//  .expr = "[in] Children"