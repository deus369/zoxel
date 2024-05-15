const double gamepad_rotate_multiplier = 0.08; // 0.09;
const double mouse_rotate_multiplier = 0.0032; // 0.008;
const float min_mouse_delta3 = 0.01f;
const float min_mouse_delta2 = 24.0f;
const float max_mouse_delta3 = 60.0f;
const float max_mouse_delta4 = 120.0f;
const float max_mouse_delta2 = 200.0f;
const double max_rotate_speed = 0.2; //  0.23;
#define disable_player_rotate_alpha_force
// shit remove this atm, it doubles up for coop
// float3 player_euler = (float3) { 0, 0, 0 };
// float3 camera_euler = (float3) { 0, 180 * degreesToRadians, 0 };

void Player3DRotateSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_in(CharacterLink, characterLinks, 3)
    zox_field_in(CameraLink, cameraLinks, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(CharacterLink, characterLinks, characterLink)
        const ecs_entity_t character = characterLink->value;
        if (!character || !zox_has(character, Character3D)) continue;
        zox_field_i_in(CameraLink, cameraLinks, cameraLink)
        if (cameraLink->value) {
            const CameraMode *cameraMode = zox_get(cameraLink->value, CameraMode)
            if (cameraMode->value != zox_camera_mode_first_person && cameraMode->value != zox_camera_mode_third_person) continue;
        }
        //if (playerState->value != zox_camera_mode_first_person) continue;
        const DisableMovement *disableMovement = zox_get(character, DisableMovement)
        if (disableMovement->value) continue;
        float2 euler = { 0, 0 };
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i_in(DeviceMode, deviceModes, deviceMode)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                float2 mouse_delta = int2_to_float2(mouse->delta);
                euler.x = - mouse_delta.y * mouse_rotate_multiplier;
                euler.y = - mouse_delta.x * mouse_rotate_multiplier;
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device_entity, Gamepad)) {
                float2 right_stick = float2_zero;
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice_entity = zevices->value[k];
                    const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                    if (zox_has(zevice_entity, ZeviceStick)) {
                        if (deviceButtonType->value == zox_device_stick_right) {
                            const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                            if (!zeviceDisabled->value) {
                                const ZeviceStick *zeviceStick = zox_get(zevice_entity, ZeviceStick)
                                right_stick = zeviceStick->value;
                                right_stick.y *= -1;
                            }
                            break;
                        }
                    }
                }
                if (float_abs(right_stick.x) >= joystick_cutoff_buffer) {
                    if (right_stick.x < -joystick_cutoff_buffer) {
                        euler.y = right_stick.x * gamepad_rotate_multiplier;
                    } else if (right_stick.x > joystick_cutoff_buffer) {
                        euler.y = right_stick.x * gamepad_rotate_multiplier;
                    }
                }
                if (float_abs(right_stick.y) >= joystick_cutoff_buffer) {
                    if (right_stick.y < -joystick_cutoff_buffer) {
                        euler.x = right_stick.y * gamepad_rotate_multiplier;
                    } else if (right_stick.y > joystick_cutoff_buffer) {
                        euler.x = right_stick.y * gamepad_rotate_multiplier;
                    }
                }
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
        // player_euler.y += euler.y;
        // player_euler.y = player_euler.y % 360;
        Euler *player_euler = zox_get_mut(character, Euler)
        Rotation3D *rotation3D = zox_get_mut(character, Rotation3D)
        player_euler->value.y += euler.y;
        rotation3D->value = quaternion_from_euler(player_euler->value);
        zox_modified(character, Rotation3D)
        zox_modified(character, Euler)
        /*camera_euler.x -= euler.x;
        if (camera_euler.x >= 180) camera_euler.x -= 360;
        else if (camera_euler.x < -180) camera_euler.x += 360;*/
        const ecs_entity_t player_camera = zox_get_value(character, CameraLink)
        if (player_camera) {
            Euler *player_camera_euler = zox_get_mut(player_camera, Euler)
            LocalRotation3D *player_camera_rotation3D = zox_get_mut(player_camera, LocalRotation3D)
            player_camera_euler->value.x -= euler.x;
            if (player_camera_euler->value.x >= 180) player_camera_euler->value.x -= 360;
            else if (player_camera_euler->value.x < -180) player_camera_euler->value.x += 360;
            player_camera_rotation3D->value = quaternion_from_euler(player_camera_euler->value);
            zox_modified(player_camera, Euler)
            zox_modified(player_camera, LocalRotation3D)
        }
#endif
    }
} zox_declare_system(Player3DRotateSystem)

// todo: make rotation by alpha force a function
/*#ifndef disable_player_rotate_alpha_force
                // if (mouse_delta != 0) zoxel_log(" > mouse_delta: %f\n", mouse_delta);
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
