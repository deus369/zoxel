unsigned char can_render_ui(ecs_world_t *world, ecs_entity_t e) {
    if (ecs_has(world, e, UIHolderLink)) {
        const UIHolderLink *uiHolderLink = ecs_get(world, e, UIHolderLink);
        if (ecs_has(world, uiHolderLink->value, RenderLod)) {
            const RenderLod *renderLod = ecs_get(world, uiHolderLink->value, RenderLod);
            if (renderLod->value == 255 || renderLod->value > 1) return 0;
        }
    }
    return 1;
}