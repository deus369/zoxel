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
