unsigned char can_render_ui(ecs_world_t *world, ecs_entity_t e) {
    if (zox_has(e, UIHolderLink)) {
        const UIHolderLink *uiHolderLink = zox_get(e, UIHolderLink)
        if (zox_has(uiHolderLink->value, RenderLod)) {
            const RenderLod *renderLod = zox_get(uiHolderLink->value, RenderLod)
            if (renderLod->value == 255 || renderLod->value > 1) return 0;
        }
    }
    if (zox_has(e, ParentLink)) {
        const ParentLink *parentLink = zox_get(e, ParentLink)
        if (parentLink->value) return can_render_ui(world, parentLink->value);
    }
    return 1;
}
