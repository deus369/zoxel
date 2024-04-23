#ifndef zoxel_hierarchy
#define zoxel_hierarchy

zox_component_byte(ChildIndex)
zox_entities_component(Children)
zox_component(ParentLink, ecs_entity_t)

// todo: macro on_destroyed_ParentLink, make Children and ParentLink declaration one thing
void on_destroyed_ParentLink(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ParentLink, parentLinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ParentLink, parentLinks, parentLink)
        if (!parentLink->value) continue;
        zox_field_e()
        Children *children = zox_get_mut(parentLink->value, Children)
        if (remove_from_Children(children, e)) zox_modified(parentLink->value, Children)
    }
}

zox_begin_module(Hierarchys)
zox_define_component_byte(ChildIndex)
zox_define_entities_component(Children)
zox_define_component(ParentLink)
ecs_observer_init(world, &(ecs_observer_desc_t) {
    .filter.expr = "ParentLink",
    .callback = on_destroyed_ParentLink,
    .events = { EcsOnRemove },
});
zoxel_end_module(Hierarchys)

#endif
