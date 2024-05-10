// #define zox_debug_billboard_system
#ifdef zox_debug_billboard_system
extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void BillboardSystem(ecs_iter_t *it) {
    // main_cameras_count
    const ecs_entity_t main_camera = main_cameras[0]; // todo: make this multi camera
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_out(Rotation3D, rotation3Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Position3D, position3Ds, position3D)
        // get closest camera
        ecs_entity_t camera = 0;
        float closest_distance = 10000;
        for (int j = 0; j < main_cameras_count; j++) {
            const float3 camera_position = zox_get_value(main_cameras[j], Position3D)
            float distance = float3_distance(position3D->value, camera_position);
            if (distance < closest_distance) {
                closest_distance = distance;
                camera = main_cameras[j];
            }
        }
        if (!camera || !zox_has(camera, Rotation3D)) continue;
        zox_field_e()
        zox_field_i_out(Rotation3D, rotation3Ds, rotation3D)
        const float4 target_rotation = zox_get_value(camera, Rotation3D)
        rotation3D->value = target_rotation;
        if (zox_has(e, Children)) {
            const Children *children = zox_get(e, Children)
            for (int j = 0; j < children->length; j++) {
                ecs_entity_t child = children->value[j];
                const LocalRotation3D *child_local_rotation3D = zox_get(child, LocalRotation3D)
                Rotation3D *child_rotation3D = zox_get_mut(child, Rotation3D)
                set_rotation_from_parents(world, e, &child_rotation3D->value, child_local_rotation3D->value);
                zox_modified(child, Rotation3D)
            }
        }
#ifdef zox_debug_billboard_system
        spawn_line3D(world, position3D->value, float3_add(position3D->value, normal), 2, 1);
#endif
    }
} zox_declare_system(BillboardSystem)
