const double movement_multiplier = 0.08 * 100;
const double shift_movement_multiplier = 3.0;

void FreeCameraMoveSystem(ecs_iter_t *it) {
    double movement_power = zox_delta_time;
    movement_power *= movement_multiplier;
#ifdef zoxel_on_web
    movement_power *= 10.0f;
#endif
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(CameraLink, cameraLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(CameraLink, cameraLinks, cameraLink)
        if (cameraLink->value == 0) continue;
        const FreeRoam *freeRoam = zox_get(cameraLink->value, FreeRoam)
        if (freeRoam->value == 0) continue;
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        float3 movement = { 0, 0, 0 };
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                if (keyboard->a.is_pressed) movement.x += -1;
                if (keyboard->d.is_pressed) movement.x += 1;
                if (keyboard->w.is_pressed) movement.z = -1;
                if (keyboard->s.is_pressed) movement.z += 1;
                if (keyboard->q.is_pressed) movement.y += -1;
                if (keyboard->e.is_pressed) movement.y = 1;
                if (keyboard->left_shift.is_pressed) {
                    movement.x *= shift_movement_multiplier;
                    movement.y *= shift_movement_multiplier;
                    movement.z *= shift_movement_multiplier;
                }
            }
        }
        if (movement.x == 0 && movement.y == 0 && movement.z == 0) continue;
        movement = float3_multiply_float(movement, movement_power);
        const Rotation3D *rotation3D = zox_get(cameraLink->value, Rotation3D)
        movement = float4_rotate_float3(rotation3D->value, movement);
        Position3D *position3D = zox_get_mut(cameraLink->value, Position3D)
        position3D->value = float3_add(position3D->value, movement);
        zox_modified(cameraLink->value, Position3D)
    }
} zox_declare_system(FreeCameraMoveSystem)

//printf("Before Movement: %fx%fx%f - [%fx%fx%fx%f]\n", movement.x, movement.y, movement.z,
//    rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
// float4_print_euler(rotation->value);
// float3 rotatedMovement2 = float3_multiply_float(rotatedMovement, 10000);
// printf("Moving [%i x %i x %i]\n", (int) rotatedMovement2.x, (int) rotatedMovement2.y, (int) rotatedMovement2.z);
// printf("    Rotation3D [%f x %f x %f x %f]\n", rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
    /*ecs_iter_t cameras_it = ecs_query_iter(it->world, it->ctx);
    ecs_query_next(&cameras_it);
    if (cameras_it.count == 0) return;*/
    /*const FreeRoam *freeRoams = ecs_field(&cameras_it, FreeRoam, 2);
    Position3D *positions = ecs_field(&cameras_it, Position3D, 3);
    Rotation3D *rotations = ecs_field(&cameras_it, Rotation3D, 4);
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++) {
        const Keyboard *keyboard = &keyboards[i];
        float3 movement = { 0, 0, 0 };
        if (keyboard->a.is_pressed) movement.x += -1;
        if (keyboard->d.is_pressed) movement.x += 1;
        if (keyboard->w.is_pressed) movement.z = -1;
        if (keyboard->s.is_pressed) movement.z += 1;
        if (keyboard->q.is_pressed) movement.y += -1;
        if (keyboard->e.is_pressed) movement.y = 1;
        if (!(movement.x == 0 && movement.y == 0 && movement.z == 0)) {
            did_update = 1;
            // printf("Bob Accel %f x %f \n", movement.x, movement.y);
            movement = float3_multiply_float(movement, movement_power);
            if (keyboard->left_shift.is_pressed) {
                movement.x *= shift_movement_multiplier;
                movement.y *= shift_movement_multiplier;
                movement.z *= shift_movement_multiplier;
            }
            for (int j = 0; j < cameras_it.count; j++) {
                const FreeRoam *freeRoam = &freeRoams[j];
                if (freeRoam->value == 1) {
                    const Rotation3D *rotation = &rotations[j];
                    float3 rotatedMovement = float4_rotate_float3(rotation->value, movement);
                    Position3D *position = &positions[j];
                    position->value = float3_add(position->value, rotatedMovement);
                }
            }
        }
        if (keyboard->r.pressed_this_frame) {
            did_update = 1;
            for (int j = 0; j < cameras_it.count; j++) {
                Rotation3D *rotation = &rotations[j];
                rotation->value = quaternion_from_euler( (float3) { 0 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
            }
        }
    }
    if (!did_update) {
        // ecs_query_skip(&cameras_it);
    }*/
