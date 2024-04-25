// todo: macro on_destroyed_ParentLink, make Children and ParentLink declaration one thing
void on_destroyed_ParentLink(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ParentLink, parentLinks, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ParentLink, parentLinks, parentLink)
        if (!parentLink->value) continue;
        if (!zox_valid(parentLink->value)) continue;
        zox_field_e()
        Children *children = zox_get_mut(parentLink->value, Children)
        if (remove_from_Children(children, e)) zox_modified(parentLink->value, Children)
    }
}
