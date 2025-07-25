// gets parent in tree's UI Holder, uses its render LOD to check if can render a 3D UI
byte can_render_ui(ecs_world_t *world, const ecs_entity_t e) {
    if (!zox_valid(e)) {
        return 0;
    }
    if (zox_has(e, UIHolderLink)) {
        zox_geter(e, UIHolderLink, uiHolderLink)
        if (zox_valid(uiHolderLink->value)) {
            if (zox_has(uiHolderLink->value, RenderLod)) {
                zox_geter(uiHolderLink->value, RenderLod, renderLod)
                if (renderLod->value == 255 || renderLod->value > 1) {
                    return 0;
                }
            }
        }
    }
    if (zox_has(e, ParentLink)) {
        zox_geter(e, ParentLink, parentLink)
        if (zox_valid(parentLink->value)) {
            return can_render_ui(world, parentLink->value);
        }
    }
    return 1;
}
