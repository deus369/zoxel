void FreeCameraMoveSystem(ecs_iter_t *it) {
    double movement_power = zox_delta_time;
    movement_power *= movement_multiplier;
#ifdef zox_web
    movement_power *= 10.0f;
#endif
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DeviceLinks)
    zox_sys_in(CameraLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(CameraLink, cameraLink)
        zox_sys_i(DeviceLinks, deviceLinks)
        if (cameraLink->value == 0) {
            continue;
        }
        const CanRoam *canRoam = zox_get(cameraLink->value, CanRoam)
        if (canRoam->value != 2) continue;
        float3 movement = { 0, 0, 0 };
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device) || zox_gett_value(device, DeviceDisabled)) {
                continue;
            }
            if (zox_has(device, Keyboard)) {
                const Keyboard *keyboard = zox_get(device, Keyboard)
                if (keyboard->a.is_pressed) movement.x += -1;
                if (keyboard->d.is_pressed) movement.x += 1;
                if (keyboard->w.is_pressed) movement.z = -1;
                if (keyboard->s.is_pressed) movement.z += 1;
                if (keyboard->q.is_pressed) movement.y += -1;
                if (keyboard->e.is_pressed) movement.y = 1;
                if (keyboard->left_shift.is_pressed) {
                    movement.x *= free_camera_run_multiplier;
                    movement.y *= free_camera_run_multiplier;
                    movement.z *= free_camera_run_multiplier;
                }
            }
        }
        if (movement.x == 0 && movement.y == 0 && movement.z == 0) {
            continue;
        }
        movement = float3_scale(movement, movement_power);
        const Rotation3D *rotation3D = zox_get(cameraLink->value, Rotation3D)
        movement = float4_rotate_float3(rotation3D->value, movement);
        Position3D *position3D = zox_get_mut(cameraLink->value, Position3D)
        position3D->value = float3_add(position3D->value, movement);
        zox_modified(cameraLink->value, Position3D)
    }
} zox_declare_system(FreeCameraMoveSystem)
