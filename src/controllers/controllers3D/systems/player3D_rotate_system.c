void Player3DRotateSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_in(CharacterLink, characterLinks, 3)
    zox_field_in(CameraLink, cameraLinks, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CharacterLink, characterLinks, characterLink)
        const ecs_entity_t character = characterLink->value;
        if (!zox_valid(character) || !zox_has(character, Character3D)) {
            continue;
        }
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        if (cameraLink->value) {
            zox_geter(cameraLink->value, CameraMode, cameraMode)
            if (cameraMode->value != zox_camera_mode_first_person && cameraMode->value != zox_camera_mode_third_person) {
                continue;
            }
        }
        zox_geter(character, DisableMovement, disableMovement)
        if (disableMovement->value) {
            continue;
        }
        float2 euler = { 0, 0 };
        float2 right_stick = float2_zero;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!zox_valid(device)) {
                continue;
            }
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device, Mouse)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (!zox_has(zevice, ZevicePointerDelta)) {
                        continue;
                    }
                    const float2 delta = int2_to_float2(zox_gett_value(zevice, ZevicePointerDelta));
                    euler.x = - delta.y * mouse_rotate_multiplier;
                    euler.y = - delta.x * mouse_rotate_multiplier;
                }
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device, Gamepad)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    zox_geter(zevice, DeviceButtonType, deviceButtonType)
                    if (zox_has(zevice, ZeviceStick)) {
                        if (deviceButtonType->value == zox_device_stick_right) {
                            zox_geter(zevice, ZeviceDisabled, zeviceDisabled)
                            if (!zeviceDisabled->value) {
                                zox_geter(zevice, ZeviceStick, zeviceStick)
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
                    if (zox_has(zevice, Finger)) {
                        continue;
                    }
                    zox_geter(zevice, ZeviceDisabled, zeviceDisabled)
                    if (zeviceDisabled->value) {
                        continue;
                    }
                    if (zox_has(zevice, ZeviceStick)) {
                        const byte joystick_type = zox_get_value(zevice, DeviceButtonType)
                        if (joystick_type == zox_device_stick_right) {
                            zox_geter(zevice, ZeviceStick, zeviceStick)
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
        if (euler.x == 0 && euler.y == 0) {
            continue;
        }
        if (zox_players_reverse_rotate_x) {
            euler.y *= -1;
        }
        if (zox_players_reverse_rotate_y) {
            euler.x *= -1;
        }
#ifndef disable_player_rotate_alpha_force
        zox_geter(character, Omega3D, omega3D)
        if ((euler.y > 0 && quaternion_to_euler_y(omega3D->value) < max_rotate_speed) || (euler.y < 0 && quaternion_to_euler_y(omega3D->value) > -max_rotate_speed)) {
            float4 quaternion = .x, euler.y(euler);
            Alpha3D *alpha3D = zox_get_mut(character, Alpha3D)
            quaternion_rotate_quaternion_p(&alpha3D->value, quaternion);
            zox_modified(character, Alpha3D)
        }
#else
        zox_get_muter(character, Euler, player_euler)
        zox_get_muter(character, Rotation3D, rotation3D)
        player_euler->value.y += euler.y;
        rotation3D->value = quaternion_from_euler(player_euler->value);
        const ecs_entity_t player_camera = zox_get_value(character, CameraLink)
        if (zox_valid(player_camera)) {
            // this sets camera x
            zox_get_muter(player_camera, Euler, player_camera_euler)
            zox_get_muter(player_camera, LocalRotation3D, player_camera_rotation3D)
            // add mouse/device input
            player_camera_euler->value.x -= euler.x;
            // makes sure to keep euler between values -180 and 180
            if (player_camera_euler->value.x >= 180 * degreesToRadians) {
                player_camera_euler->value.x -= 360 * degreesToRadians;
            } else if (player_camera_euler->value.x < -180 * degreesToRadians) {
                player_camera_euler->value.x += 360 * degreesToRadians;
            }
            // limit camera for player head
            float2 limit_camera_x = (float2) { 89, 89 };
            if (player_camera_euler->value.x > limit_camera_x.x * degreesToRadians)  {
                player_camera_euler->value.x = limit_camera_x.x * degreesToRadians;
            } else if (player_camera_euler->value.x < -limit_camera_x.y * degreesToRadians) {
                player_camera_euler->value.x = -limit_camera_x.y * degreesToRadians;
            }
            player_camera_rotation3D->value = quaternion_from_euler(player_camera_euler->value);
        }
#endif
    }
} zox_declare_system(Player3DRotateSystem)