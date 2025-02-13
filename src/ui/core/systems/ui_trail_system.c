#ifdef zox_debug_ui_trails
    float ui_trail_debug_thickness = 2.0f;
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void UITrailSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(UIHolderLink, uiHolderLinks, 1)
    zox_field_in(UITrail, uiTrails, 2)
    zox_field_out(Position3D, position3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(UIHolderLink, uiHolderLinks, uiHolderLink)
        if (!uiHolderLink->value) continue;
        zox_field_e()
        zox_field_i(UITrail, uiTrails, uiTrail)
        zox_field_o(Position3D, position3Ds, position3D)
        position3D->value = uiTrail->value;
        const Position3D *target_position = zox_get(uiHolderLink->value, Position3D)
        float3_add_float3_p(&position3D->value, target_position->value);
        if (zox_has(e, Children)) {
            const Children *children = zox_get(e, Children)
            for (int j = 0; j < children->length; j++) {
                const ecs_entity_t child = children->value[j];
                const LocalPosition3D *child_local_position3D = zox_get(child, LocalPosition3D)
                Position3D *child_position3D = zox_get_mut(child, Position3D)
                set_position_from_parents(world, e, &child_position3D->value, child_local_position3D->value);
                zox_modified(child, Position3D)
            }
        }
#ifdef zox_debug_ui_trails
        spawn_line3D(world, target_position->value, position3D->value, ui_trail_debug_thickness, 1.0);
#endif
    }
} zox_declare_system(UITrailSystem)
