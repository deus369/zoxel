
void Player3DRotateSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_in(CharacterLink, characterLinks, 3)
    zox_field_in(CameraLink, cameraLinks, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CharacterLink, characterLinks, characterLink)
        const ecs_entity_t character = characterLink->value;
        if (!character || !zox_has(character, Character3D)) continue;
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        if (cameraLink->value) {
            const CameraMode *cameraMode = zox_get(cameraLink->value, CameraMode)
            if (cameraMode->value != zox_camera_mode_first_person && cameraMode->value != zox_camera_mode_third_person) continue;
        }
        //if (playerState->value != zox_camera_mode_first_person) continue;
        const DisableMovement *disableMovement = zox_get(character, DisableMovement)
        if (disableMovement->value) continue;
        float2 euler = { 0, 0 };
        float2 right_stick = float2_zero;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) continue;
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device, Mouse)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (!zox_has(zevice, ZevicePointerDelta)) continue;
                    const float2 delta = int2_to_float2(zox_gett_value(zevice, ZevicePointerDelta));
                    euler.x = - delta.y * mouse_rotate_multiplier;
                    euler.y = - delta.x * mouse_rotate_multiplier;
                }
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device, Gamepad)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    const DeviceButtonType *deviceButtonType = zox_get(zevice, DeviceButtonType)
                    if (zox_has(zevice, ZeviceStick)) {
                        if (deviceButtonType->value == zox_device_stick_right) {
                            const ZeviceDisabled *zeviceDisabled = zox_get(zevice, ZeviceDisabled)
                            if (!zeviceDisabled->value) {
                                const ZeviceStick *zeviceStick = zox_get(zevice, ZeviceStick)
                                right_stick.x += zeviceStick->value.x;
                                right_stick.y -= zeviceStick->value.y;
                            }
                            break;
                        }
                    }
                }
            } else if (deviceMode->value == zox_device_mode_touchscreen && zox_has(device, Touchscreen)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (zox_has(zevice, Finger)) continue;
                    const ZeviceDisabled *zeviceDisabled = zox_get(zevice, ZeviceDisabled)
                    if (zeviceDisabled->value) continue;
                    if (zox_has(zevice, ZeviceStick)) {
                        const byte joystick_type = zox_get_value(zevice, DeviceButtonType)
                        if (joystick_type == zox_device_stick_right) {
                            const ZeviceStick *zeviceStick = zox_get(zevice, ZeviceStick)
                            right_stick.x -= zeviceStick->value.x * touchscreen_rotate_multiplier;
                            right_stick.y -= zeviceStick->value.y * touchscreen_rotate_multiplier;
                        }
                    }
                }
            }
        }
        if (float_abs(right_stick.x) >= joystick_cutoff_buffer) {
            if (right_stick.x < -joystick_cutoff_buffer) {
                euler.y = right_stick.x * gamepad_rotate_multiplier_x;
            } else if (right_stick.x > joystick_cutoff_buffer) {
                euler.y = right_stick.x * gamepad_rotate_multiplier_x;
            }
        }
        if (float_abs(right_stick.y) >= joystick_cutoff_buffer) {
            if (right_stick.y < -joystick_cutoff_buffer) {
                euler.x = right_stick.y * gamepad_rotate_multiplier_y;
            } else if (right_stick.y > joystick_cutoff_buffer) {
                euler.x = right_stick.y * gamepad_rotate_multiplier_y;
            }
        }
        if (euler.x == 0 && euler.y == 0) continue;
        if (zox_players_reverse_rotate_x) euler.y *= -1;
        if (zox_players_reverse_rotate_y) euler.x *= -1;
#ifndef disable_player_rotate_alpha_force
        const Omega3D *omega3D = zox_get(character, Omega3D)
        if ((euler.y > 0 && quaternion_to_euler_y(omega3D->value) < max_rotate_speed) || (euler.y < 0 && quaternion_to_euler_y(omega3D->value) > -max_rotate_speed)) {
            float4 quaternion = .x, euler.y(euler);
            Alpha3D *alpha3D = zox_get_mut(character, Alpha3D)
            quaternion_rotate_quaternion_p(&alpha3D->value, quaternion);
            zox_modified(character, Alpha3D)
        }
#else
        Euler *player_euler = zox_get_mut(character, Euler)
        Rotation3D *rotation3D = zox_get_mut(character, Rotation3D)
        player_euler->value.y += euler.y;
        rotation3D->value = quaternion_from_euler(player_euler->value);
        zox_modified(character, Rotation3D)
        zox_modified(character, Euler)
        const ecs_entity_t player_camera = zox_get_value(character, CameraLink)
        if (player_camera) {
            // this sets camera x
            zox_get_muter(player_camera, Euler, player_camera_euler)
            // add mouse/device input
            player_camera_euler->value.x -= euler.x;
            // makes sure to keep euler between values -180 and 180
            if (player_camera_euler->value.x >= 180 * degreesToRadians) player_camera_euler->value.x -= 360 * degreesToRadians;
            else if (player_camera_euler->value.x < -180 * degreesToRadians) player_camera_euler->value.x += 360 * degreesToRadians;
            // limit camera for player head
            float2 limit_camera_x = (float2) { 89, 89 };
            if (player_camera_euler->value.x > limit_camera_x.x * degreesToRadians) player_camera_euler->value.x = limit_camera_x.x * degreesToRadians;
            else if (player_camera_euler->value.x < -limit_camera_x.y * degreesToRadians) player_camera_euler->value.x = -limit_camera_x.y * degreesToRadians;
            // zox_log(" > player_camera_euler->value.x [%f]\n", player_camera_euler->value.x)
            // synch up rotation immediately
            zox_get_muter(player_camera, LocalRotation3D, player_camera_rotation3D)
            player_camera_rotation3D->value = quaternion_from_euler(player_camera_euler->value);
        }
#endif
    }
} zox_declare_system(Player3DRotateSystem)

// todo: make rotation by alpha force a function
/*#ifndef disable_player_rotate_alpha_force
    // if (mouse_delta != 0) zox_log(" > mouse_delta: %f\n", mouse_delta);
    // this is all pretty shit ay haha... fuck mouses
    if (mouse_delta < -max_mouse_delta2) mouse_delta.x = -max_mouse_delta;
    else if (mouse_delta > max_mouse_delta2) mouse_delta.x = max_mouse_delta;
    if (float_abs(mouse_delta) >= max_mouse_delta3) mouse_delta.x *= 1.2f;
    else if (float_abs(mouse_delta) >= max_mouse_delta4) mouse_delta.x *= 1.4f;
    else if (float_abs(mouse_delta) <= min_mouse_delta3) mouse_delta.x = 0;
    if (mouse_delta.x != 0) {
        if (mouse_delta.x > 0 && mouse_delta < min_mouse_delta2) mouse_delta.x = min_mouse_delta2;
        else if (mouse_delta < 0 && mouse_delta > -min_mouse_delta2) mouse_delta.x = -min_mouse_delta2;
    }
#endif*/
// if (mouse_delta != 0) zoxel_log("     > mouse_delta: %f\n", mouse_delta);
