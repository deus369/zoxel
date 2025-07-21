/*
 * ==========================================
 *          PLAYER MOVEMENT SYSTEM
 * ==========================================
 *
 * This is the magic behind the player's smooth and responsive movement!
 * Ever wondered how your character darts and dashes through the game world with such finesse?
 * Look no further! This system ensures your player obeys the laws of physics while still
 * feeling like a nimble acrobat.
 *
 * Features:
 * - Supports walking, running, and everything in between!
 * - Ensures speed limits are respected (no speedsters allowed beyond the max speed!).
 * - Seamlessly integrates with your game world's orientation, so movement always feels natural.
 *
 * Enjoy the thrill of movement, and remember: with great speed comes great responsibility!
 *
 * ==========================================
 * Code responsibly, have fun, and may your bugs be few and far between!
 * ==========================================
 */

#ifdef zox_debug_player_movement_direction
float debug_thickness = 2.0f;
extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void Player3DMoveSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_field_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_in(CharacterLink, characterLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CharacterLink, characterLinks, characterLink)
        const ecs_entity_t character = characterLink->value;
        if (!zox_valid(character) || !zox_has(character, Character3D)) {
            continue;
        }
        zox_geter(character, DisableMovement, disableMovement)
        if (disableMovement->value) {
            continue;
        }
        float2 left_stick = float2_zero;
        byte is_running = 0;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (!device) {
                continue;
            }
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device, Keyboard)) {
                zox_geter(device, Keyboard, keyboard)
                if (keyboard->w.is_pressed) left_stick.y += 1;
                if (keyboard->s.is_pressed) left_stick.y -= 1;
                if (keyboard->a.is_pressed) left_stick.x += 1;
                if (keyboard->d.is_pressed) left_stick.x += -1;
                if (keyboard->left_shift.is_pressed) is_running = 1;
                // float2_normalize_p(&left_stick);
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device, Gamepad)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice_entity = zevices->value[k];
                    zox_geter(zevice_entity, ZeviceDisabled, zeviceDisabled)
                    if (zeviceDisabled->value) {
                        continue;
                    }
                    zox_geter(zevice_entity, DeviceButtonType, deviceButtonType)
                    if (zox_has(zevice_entity, ZeviceStick)) {
                        if (deviceButtonType->value == zox_device_stick_left) {
                            zox_geter(zevice_entity, ZeviceStick, zeviceStick)
                            left_stick.x += zeviceStick->value.x; // joysticks are weird
                            left_stick.y += zeviceStick->value.y;
                        }
                    } else if (zox_has(zevice_entity, ZeviceButton)) {
                        if (deviceButtonType->value == zox_device_button_lb || deviceButtonType->value == zox_device_button_rb) {
                            zox_geter(zevice_entity, ZeviceButton, zeviceButton)
                            if (!is_running && devices_get_is_pressed(zeviceButton->value)) {
                                is_running = 1;
                            }
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
                        if (joystick_type == zox_device_stick_left) {
                            const ZeviceStick *zeviceStick = zox_get(zevice, ZeviceStick)
                            left_stick.x -= zeviceStick->value.x;
                            left_stick.y += zeviceStick->value.y;
                        }
                    }
                }
            }
        }
        if (left_stick.x == 0 && left_stick.y == 0) {
            continue;
        }
        if (zox_players_reverse_x) {
            left_stick.x *= -1;
        }
        if (zox_players_reverse_y) {
            left_stick.y *= -1;
        }
        float3 movement = { left_stick.x * player_movement_power.x, 0, left_stick.y * player_movement_power.y };
        if (is_running) {
            movement.x *= run_accceleration;
            movement.y *= run_accceleration;
        }
        // float delta_time_adjustment = 1.0f / (60 * delta_time);
        // float3_scale_p(&movement, delta_time_adjustment);
        float4 movement_rotation = float4_identity;
        zox_geter(character, Rotation3D, rotation3D)
        zox_geter(character, Velocity3D, velocity3D)
        zox_get_muter(character, Acceleration3D, acceleration3D)
        if (camera_mode == zox_camera_mode_topdown || camera_mode == zox_camera_mode_ortho) {
            if (zox_has(character, CameraLink)) {
                zox_geter(character, CameraLink, cameraLink)
                if (cameraLink->value) {
                    zox_geter(cameraLink->value, Rotation3D, camera_rotation)
                    const float4 camera_rotation2 = quaternion_from_euler((float3) { 0, -quaternion_to_euler_y(camera_rotation->value), 0 });
                    if (movement.z == -movement.x) {
                        movement.x *= 0.999f; // this hack fixes the rotation
                    }
                    movement_rotation = camera_rotation2;
                    float4 face_direction = quaternion_from_between_vectors(float3_forward, movement);
                    // test rotation
                    Rotation3D *rotation3D2 = zox_get_mut(character, Rotation3D)
                    rotation3D2->value = face_direction;
                    zox_modified(character, Rotation3D)
#ifdef zox_debug_player_movement_direction
                    const Position3D *position3D = zox_get(character, Position3D)
                    spawn_line3D(world, position3D->value, float3_add(position3D->value, movement), debug_thickness, 34.0);
                    float3 movement2 = float4_rotate_float3(face_direction, (float3) { 0, 0, -1 });
                    spawn_line3D(world, position3D->value, float3_add(position3D->value, movement2), debug_thickness, 34.0);
                    zox_log(" > face_direction %fx%fx%fx%f\n", face_direction.x, face_direction.y, face_direction.z, face_direction.w);
#endif
                }
            }
        } else {
            movement_rotation = rotation3D->value;
        }
        // here we use two vectors for movement directions so we can limit them
        // we also use a potential velocity based on a calculated new velocity
        // (although we dont know delta_time next frame)
        float2 max_speed = max_velocity3D;
        if (is_running) {
            max_speed.x *= run_speed;
            max_speed.y *= run_speed;
        }

        float3 movement_real_z = float4_rotate_float3(movement_rotation, (float3) { 0, 0, movement.z });
        movement_real_z.y = 0;

        float3 movement_real_x = float4_rotate_float3(movement_rotation, (float3) { movement.x, 0, 0 });
        movement_real_x.y = 0;

        float4 inverse_rotation = float4_inverse(rotation3D->value);
        float3 velocity_local = float4_rotate_float3(inverse_rotation, velocity3D->value);
        float3 acceleration_local = float4_rotate_float3(inverse_rotation, acceleration3D->value);

        float3 potential_velocity_forward = { 0, 0, velocity_local.z + (acceleration_local.z + movement.y) * delta_time };
        float3 potential_velocity_left = { velocity_local.x + (acceleration_local.x + movement.x) * delta_time, 0, 0 };

        if (float_abs(potential_velocity_forward.z) < max_speed.y) {
            float3_add_float3_p(&acceleration3D->value, movement_real_z);
        }
        if (float_abs(potential_velocity_left.x) < max_speed.x) {
            float3_add_float3_p(&acceleration3D->value, movement_real_x);
        }

#ifdef zox_debug_player_speed_limits
        if (float_abs(potential_velocity_left.x) < max_speed.x) zox_log(" > under maximum velocity x: %f\n", potential_velocity_left.x)
        else zox_log(" > past maximum velocity x: %f\n", potential_velocity_left.x)
        if (float_abs(potential_velocity_forward.z) < max_speed.y) zox_log(" > under maximum velocity z: %f\n", potential_velocity_forward.z)
        else zox_log(" > past maximum velocity z: %f\n", potential_velocity_forward.z)
#endif
    }
} zox_declare_system(Player3DMoveSystem)