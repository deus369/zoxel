#ifdef zox_debug_ui_trails
    float ui_trail_debug_thickness = 2.0f;
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void UITrailSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(UIHolderLink)
    zox_sys_in(UITrail)
    zox_sys_out(Position3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(UIHolderLink, uiHolderLink)
        zox_sys_i(UITrail, uiTrail)
        zox_sys_o(Position3D, position3D)
        if (!zox_valid(uiHolderLink->value)) {
            if (uiHolderLink->value) {
                zox_sys_e()
                zox_log("! character ui wasn't destroyed: %lu\n", e)
                zox_delete(e)
            }
            continue;
        }
        position3D->value = uiTrail->value;
        const Position3D *target_position = zox_get(uiHolderLink->value, Position3D)
        float3_add_float3_p(&position3D->value, target_position->value);
        if (zox_has(e, Children)) {
            const Children *children = zox_get(e, Children)
            for (int j = 0; j < children->length; j++) {
                const ecs_entity_t child = children->value[j];
                zox_geter(child, LocalPosition3D, child_local_position3D)
                zox_get_muter(child, Position3D, child_position3D)
                set_position_from_parents(world, e, &child_position3D->value, child_local_position3D->value);
            }
        }
#ifdef zox_debug_ui_trails
        spawn_line3D(world, target_position->value, position3D->value, ui_trail_debug_thickness, 1.0);
#endif
    }
} zox_declare_system(UITrailSystem)
