void disable_element_rendering(ecs_world_t *world, const ecs_entity_t e, const unsigned char disabled) {
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
