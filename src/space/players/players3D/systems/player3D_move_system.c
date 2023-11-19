const double jump_power = 12.0;
const double movement_power_x = 6; // 16;
const double movement_power_z = 9; // 24;
const float2 max_velocity = { 60 * 60, 160 * 60 };
const double run_speed = 1.6;
const float backwards_multiplier = 0.7f;

#ifdef zox_debug_player_movement_direction
    float debug_thickness = 2.0f;
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void Player3DMoveSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    float2 max_delta_velocity = max_velocity;
    max_delta_velocity.x *= delta_time;
    max_delta_velocity.y *= delta_time;
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 2)
    zox_field_in(DeviceMode, deviceModes, 3)
    zox_field_in(CharacterLink, characterLinks, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(CharacterLink, characterLinks, characterLink)
        if (!characterLink->value) continue;
        const DisableMovement *disableMovement = zox_get(characterLink->value, DisableMovement)
        if (disableMovement->value) continue;
        float2 left_stick = float2_zero;
        unsigned char is_running = 0;
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i_in(DeviceMode, deviceModes, deviceMode)
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device_entity, Keyboard)) {
                const Keyboard *keyboard = zox_get(device_entity, Keyboard)
                if (keyboard->w.is_pressed) left_stick.y += 1;
                if (keyboard->s.is_pressed) left_stick.y -= 1;
                if (keyboard->a.is_pressed) left_stick.x += 1;
                if (keyboard->d.is_pressed) left_stick.x += -1;
                if (keyboard->left_shift.is_pressed) is_running = 1;
                // float2_normalize_p(&left_stick);
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device_entity, Gamepad)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                    if (zeviceDisabled->value) continue;
                    const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                    if (zox_has(zevice_entity, ZeviceStick)) {
                        if (deviceButtonType->value == zox_device_stick_left) {
                            const ZeviceStick *zeviceStick = zox_get(zevice_entity, ZeviceStick)
                            left_stick.x += zeviceStick->value.x; // joysticks are weird
                            left_stick.y += zeviceStick->value.y;
                        }
                    } else if (zox_has(zevice_entity, ZeviceButton)) {
                        if (deviceButtonType->value == zox_device_button_lb || deviceButtonType->value == zox_device_button_rb) {
                            const ZeviceButton *zeviceButton = zox_get(zevice_entity, ZeviceButton)
                            if (!is_running && devices_get_is_pressed(zeviceButton->value)) is_running = 1;
                        }
                    }
                }
            } else if (deviceMode->value == zox_device_mode_touchscreen && zox_has(device_entity, Touchscreen)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    if (k < fingers_count) continue;
                    ecs_entity_t zevice_entity = zevices->value[k];
                    const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                    if (zeviceDisabled->value) continue;
                    if (zox_has(zevice_entity, ZeviceStick)) {
                        const ZeviceStick *zeviceStick = zox_get(zevice_entity, ZeviceStick)
                        left_stick.x -= zeviceStick->value.x;
                        left_stick.y += zeviceStick->value.y;
                    }
                }
            }
        }
        if (left_stick.x == 0 && left_stick.y == 0) continue;
        // zoxel_log(" > left_stick %fx%f\n", left_stick.x, left_stick.y);
        float3 movement = { left_stick.x, 0, left_stick.y };
        // const Omega3D *omega3D = zox_get(world, characterLink->value, Omega3D);
        const Rotation3D *rotation3D = zox_get(characterLink->value, Rotation3D)
        const Velocity3D *velocity3D = zox_get(characterLink->value, Velocity3D)
        Acceleration3D *acceleration3D = zox_get_mut(characterLink->value, Acceleration3D)
        if (camera_mode == zox_camera_mode_topdown || camera_mode == zox_camera_mode_ortho) {
            if (zox_has(characterLink->value, CameraLink)) {
                const CameraLink *cameraLink = zox_get(characterLink->value, CameraLink)
                if (cameraLink->value) {
                    const Rotation3D *camera_rotation = zox_get(cameraLink->value, Rotation3D)
                    float4 camera_rotation2 = quaternion_from_euler((float3) { 0, -quaternion_to_euler_y(camera_rotation->value), 0 });
                    if (movement.z == -movement.x) movement.x *= 0.999f; // this hack fixes the rotation
                    movement = float4_rotate_float3(camera_rotation2, movement);
                    movement.y = 0;
                    // movement = float3_normalize(movement);
                    float4 face_direction = quaternion_from_between_vectors(float3_forward, movement);
                    // test rotation
                    Rotation3D *rotation3D2 = zox_get_mut(characterLink->value, Rotation3D)
                    rotation3D2->value = face_direction;
                    zox_modified(characterLink->value, Rotation3D)
                    // todo: rotate towards desired direction
                    // Alpha3D *alpha3D = zox_get_mut(world, characterLink->value, Alpha3D);
                    // quaternion_rotate_quaternion_p(&alpha3D->value, quaternion);
                    // ecs_modified(world, characterLink->value, Alpha3D);
                    #ifdef zox_debug_player_movement_direction
                        const Position3D *position3D = zox_get(characterLink->value, Position3D)
                        spawn_line3D(world, position3D->value, float3_add(position3D->value, movement), debug_thickness, 34.0);
                        float3 movement2 = float4_rotate_float3(face_direction, (float3) { 0, 0, -1 });
                        spawn_line3D(world, position3D->value, float3_add(position3D->value, movement2), debug_thickness, 34.0);
                        // zoxel_log(" > movement: %fx%fx%f\n", movement.x, movement.y, movement.z);
                        // zoxel_log("     - movement2: %fx%fx%f\n", movement2.x, movement2.y, movement.z);
                        zoxel_log(" > face_direction %fx%fx%fx%f\n", face_direction.x, face_direction.y, face_direction.z, face_direction.w);
                    #endif
                }
            }
        } else {
            movement = float4_rotate_float3(rotation3D->value, movement);
        }
        if (is_running) {
            movement.x *= run_speed;
            movement.z *= run_speed;
        }
        // if (movement.z < 0) movement.z *= backwards_multiplier;
        float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
        if (float_abs(rotated_velocity.x) < max_delta_velocity.x) acceleration3D->value.x += movement.x * movement_power_x;
        if (float_abs(rotated_velocity.z) < max_delta_velocity.y) acceleration3D->value.z += movement.z * movement_power_z;
        zox_modified(characterLink->value, Acceleration3D)
    }
} zox_declare_system(Player3DMoveSystem)
