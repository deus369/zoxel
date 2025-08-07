#define find_child_with_tag(parent, tag, child_name)\
    const Children *children_##tag = zox_get(parent, Children)\
    entity child_name = 0;\
    for (int i = 0; i < children_##tag->length; i++) {\
        const entity child_e = children_##tag->value[i];\
        if (child_e && zox_has(child_e, tag)) {\
            child_name = child_e;\
            break;\
        }\
    }

#define find_child_with_id(parent, id, child_name)\
    const Children *children = zox_get(parent, Children)\
    entity child_name = 0;\
    for (int i = 0; i < children->length; i++) {\
        const entity child_e = children->value[i];\
        if (child_e && zox_has_id(child_e, id)) {\
            child_name = child_e;\
            break;\
        }\
    }

#define if_has_child_with_tag(e, tag)\
entity child_##tag = 0;\
const Children *children_##tag = zox_get(e, Children)\
for (int i = 0; i < children_##tag->length; i++) {\
    const entity child_e = children_##tag->value[i];\
    if (child_e && zox_has(child_e, tag)) {\
        child_##tag = child_e;\
        break;\
    }\
}\
if (child_##tag)


#define if_has_child_with_id(e, tag)\
    entity child = 0;\
    const Children *children = zox_get(e, Children)\
    for (int i = 0; i < children->length; i++) {\
        const entity child_e = children->value[i];\
        if (child_e && zox_has_id(child_e, tag)) {\
            child = child_e;\
            break;\
        }\
    }\
    if (child)

void on_child_added(ecs *world,
    const entity parent,
    const entity child)
{
    // zox_log(" + added [%lu] to canvas [%lu]\n", e, canvas)
    // todo: make this generic for when component is set, event
    // this isn't systematic enough for children linking!
    Children *children = zox_get_mut(parent, Children)
    if (add_to_Children(children, child)) {
        zox_modified(parent, Children)
    }
}

void zox_debug_children(ecs *world,
    const entity parent)
{
    Children *children = zox_get_mut(parent, Children)
    zox_log(" > children of [%s]\n", zox_get_name(parent))
    for (int i = 0; i < children->length; i++) {
        const entity child = children->value[i];
        zox_log("       - child [%s]\n", zox_get_name(child))
    }
}
