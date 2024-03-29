const double gamepad_rotate_multiplier = 0.08; // 0.09;
const double mouse_rotate_multiplier = 0.0032; // 0.008;
const float min_mouse_delta3 = 0.01f;
const float min_mouse_delta2 = 24.0f;
const float max_mouse_delta3 = 60.0f;
const float max_mouse_delta4 = 120.0f;
const float max_mouse_delta2 = 200.0f;
const double max_rotate_speed = 0.2; //  0.23;

float4 mouse_delta_to_rotation(float deltaX, float deltaY) {
    float4 output = quaternion_identity;
    output.x = deltaX;
    output.y = deltaY;
    // quaternion_normalize(&output);
    return output;
}

void Player3DRotateSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 2)
    zox_field_in(CharacterLink, characterLinks, 3)
    zox_field_in(CameraLink, cameraLinks, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(CharacterLink, characterLinks, characterLink)
        ecs_entity_t character = characterLink->value;
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
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                float mouse_delta = mouse->delta.x;
                // if (mouse_delta != 0) zoxel_log(" > mouse_delta: %f\n", mouse_delta);
                // this is all pretty shit ay haha... fuck mouses
                if (mouse_delta < -max_mouse_delta2) mouse_delta = -max_mouse_delta;
                else if (mouse_delta > max_mouse_delta2) mouse_delta = max_mouse_delta;
                if (float_abs(mouse_delta) >= max_mouse_delta3) mouse_delta *= 1.2f;
                else if (float_abs(mouse_delta) >= max_mouse_delta4) mouse_delta *= 1.4f;
                else if (float_abs(mouse_delta) <= min_mouse_delta3) mouse_delta = 0;
                if (mouse_delta != 0) {
                    if (mouse_delta > 0 && mouse_delta < min_mouse_delta2) mouse_delta = min_mouse_delta2;
                    else if (mouse_delta < 0 && mouse_delta > -min_mouse_delta2) mouse_delta = -min_mouse_delta2;
                }
                // if (mouse_delta != 0) zoxel_log("     > mouse_delta: %f\n", mouse_delta);
                euler.y = - mouse_delta * mouse_rotate_multiplier;
            } else if (zox_has(device_entity, Gamepad)) {
                float2 right_stick = float2_zero;
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                    if (zox_has(zevice_entity, ZeviceStick)) {
                        if (deviceButtonType->value == zox_device_stick_right) {
                            const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                            if (!zeviceDisabled->value) {
                                const ZeviceStick *zeviceStick = zox_get(zevice_entity, ZeviceStick)
                                right_stick = zeviceStick->value;
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
            }
        }
        if (euler.x == 0 && euler.y == 0) continue;
        const Omega3D *omega3D = zox_get(character, Omega3D)
        if ((euler.y > 0 && quaternion_to_euler_y(omega3D->value) < max_rotate_speed) || (euler.y < 0 && quaternion_to_euler_y(omega3D->value) > -max_rotate_speed)) {
            float4 quaternion = mouse_delta_to_rotation(euler.x, euler.y);
            Alpha3D *alpha3D = zox_get_mut(character, Alpha3D)
            quaternion_rotate_quaternion_p(&alpha3D->value, quaternion);
            zox_modified(character, Alpha3D)
        }
    }
} zox_declare_system(Player3DRotateSystem)
