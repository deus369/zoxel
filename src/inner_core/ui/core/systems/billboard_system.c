// #define zox_debug_billboard_system
#ifdef zox_debug_billboard_system
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void BillboardSystem(ecs_iter_t *it) {
    // return;
    ecs_entity_t main_camera = main_cameras[0];
    // float4 flip_rotation = quaternion_from_euler((float3) { 0, 180 * degreesToRadians, 0 });
    ecs_world_t *world = it->world;
    // const CameraLink *cameraLinks = ecs_field(it, CameraLink, 2);
    // const Position3D *position3Ds = ecs_field(it, Position3D, 3);
    Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 4);
    for (int i = 0; i < it->count; i++) {
        // const CameraLink *cameraLink = &cameraLinks[i];
        ecs_entity_t camera = main_camera; // cameraLink->value
        if (!camera || !ecs_has(world, camera, Rotation3D)) continue;
        ecs_entity_t e = it->entities[i];
        // const Position3D *position3D = &position3Ds[i];
        Rotation3D *rotation3D = &rotation3Ds[i];
        const Rotation3D *target_rotation = ecs_get(world, camera, Rotation3D);
        // rotation3D->value = quaternion_rotate(flip_rotation, target_rotation->value);
        rotation3D->value = target_rotation->value;
        if (ecs_has(world, e, Children)) {
            const Children *children = ecs_get(world, e, Children);
            for (int j = 0; j < children->length; j++) {
                ecs_entity_t child = children->value[j];
                const LocalRotation3D *child_local_rotation3D = ecs_get_mut(world, child, LocalRotation3D);
                Rotation3D *child_rotation3D = ecs_get_mut(world, child, Rotation3D);
                set_rotation_from_parents(world, e, &child_rotation3D->value, child_local_rotation3D->value);
                ecs_modified(world, child, Rotation3D);
            }
        }
        #ifdef zox_debug_billboard_system
            spawn_line3D(world, position3D->value, float3_add(position3D->value, normal), 2, 1);
        #endif
    }
} zox_declare_system(BillboardSystem)

/*const Position3D *target_position = ecs_get(world, cameraLink->value, Position3D);
// float3 delta = float3_subtract_float3(position3D->value, target_position->value);
float3 delta = float3_subtract_float3(target_position->value, position3D->value);
float3 normal = float3_normalize(delta);
// rotation3D->value = quaternion_from_float3(normal); // turn to quaternion
rotation3D->value = float3ToQuaternion(delta);
#ifdef zox_debug_billboard_system
    // spawn_line3D(world, position3D->value, float3_add(position3D->value, normal), 2, 1);
    spawn_line3D(world, position3D->value, float3_add(position3D->value, delta), 2, 1);
    // zoxel_log(" > normal [%fx%fx%f]\n", normal.x, normal.y, normal.z);
    // zoxel_log("     - delta [%fx%fx%f]\n", delta.x, delta.y, delta.z);
#endif*/