// #define zox_debug_billboard_system
#ifdef zox_debug_billboard_system
extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void BillboardSystem(ecs_iter_t *it) {
    if (main_cameras_count == 0) return;
    zox_field_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_out(Rotation3D, rotation3Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3D, position3Ds, position3D)
        const ecs_entity_t camera = find_closest_camera(world, position3D->value);
        if (!camera || !zox_has(camera, Rotation3D)) continue;
        zox_field_e()
        zox_field_o(Rotation3D, rotation3Ds, rotation3D)
        const float4 target_rotation = zox_get_value(camera, Rotation3D)
        rotation3D->value = target_rotation;
        if (zox_has(e, Children)) {
            const Children *children = zox_get(e, Children)
            for (int j = 0; j < children->length; j++) {
                ecs_entity_t child = children->value[j];
                if (!zox_has(child, LocalRotation3D)) {
                    // zox_log("! billboard child [%i:%s] doesn't have [LocalRotation3D]\n", j, zox_get_name(child))
                    continue;
                }
                const float4 child_local_rotation3D = zox_get_value(child, LocalRotation3D)
                Rotation3D *child_rotation3D = zox_get_mut(child, Rotation3D)
                set_rotation_from_parents(world, e, &child_rotation3D->value, child_local_rotation3D);
                zox_modified(child, Rotation3D)
            }
        }
#ifdef zox_debug_billboard_system
        spawn_line3D(world, position3D->value, float3_add(position3D->value, normal), 2, 1);
#endif
    }
} zox_declare_system(BillboardSystem)
