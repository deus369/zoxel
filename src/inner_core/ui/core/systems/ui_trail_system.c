void UITrailSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const UIHolderLink *uiHolderLinks = ecs_field(it, UIHolderLink, 1);
    const UITrail *uiTrails = ecs_field(it, UITrail, 2);
    Position3D *position3Ds = ecs_field(it, Position3D, 3);
    for (int i = 0; i < it->count; i++) {
        const UIHolderLink *uiHolderLink = &uiHolderLinks[i];
        if (uiHolderLink->value == 0) continue;
        const UITrail *uiTrail = &uiTrails[i];
        Position3D *position3D = &position3Ds[i];
        const Position3D *target_position = ecs_get(world, uiHolderLink->value, Position3D);
        position3D->value = uiTrail->value;
        float3_add_float3_p(&position3D->value, target_position->value);
    }
} zox_declare_system(UITrailSystem)