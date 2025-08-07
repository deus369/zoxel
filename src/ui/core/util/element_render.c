void disable_element_rendering(ecs *world, const entity e, const byte disabled) {
    if (!zox_has(e, RenderDisabled)) return;
    RenderDisabled *renderDisabled = zox_get_mut(e, RenderDisabled)
    renderDisabled->value = disabled;
    zox_modified(e, RenderDisabled)
    if (zox_has(e, Children)) {
        const Children *children = zox_get(e, Children)
        if (children) {
            for (int i = 0; i < children->length; i++) disable_element_rendering(world, children->value[i], disabled);
        }
    }
}
