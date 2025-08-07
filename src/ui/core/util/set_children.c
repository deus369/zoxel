// set all to disabled for example, or enabled -> useful for toggling
void set_children_component_byte(ecs* world,
    entity e,
    entity id,
    const byte value)
{
    if (zox_has_id(e, id)) {
        zox_set_id(e, id, 1, value)
    }
    if (zox_has(e, Children)) {
        zox_geter(e, Children, children)
        for (int i = 0; i < children->length; i++) {
            set_children_component_byte(world, children->value[i], id, value);
        }
    }
}