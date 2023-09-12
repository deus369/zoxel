const double jump_power = 12.0;
const double movement_power_x = 6; // 16;
const double movement_power_z = 9; // 24;
const float2 max_velocity = { 60 * 60, 160 * 60 };
const double run_speed = 1.6;
const float backwards_multiplier = 0.7f;
// #define zox_floating_movement
// todo: get rotated velocity to test max
// #define zox_debug_player_movement_direction

#ifdef zox_debug_player_movement_direction
    float debug_thickness = 2.0f;
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void Player3DMoveSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    double delta_time = zox_delta_time;
    float2 max_delta_velocity = max_velocity;
    max_delta_velocity.x *= delta_time;
    max_delta_velocity.y *= delta_time;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 3);
    const CharacterLink *characterLinks = ecs_field(it, CharacterLink, 4);
    for (int i = 0; i < it->count; i++) {
        const CharacterLink *characterLink = &characterLinks[i];
        if (!characterLink->value) continue;
        const DisableMovement *disableMovement = ecs_get(world, characterLink->value, DisableMovement);
        if (disableMovement->value) continue;
        float2 left_stick = float2_zero;
        unsigned char is_running = 0;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        const DeviceMode *deviceMode = &deviceModes[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_keyboardmouse && ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->w.is_pressed) left_stick.y += 1;
                if (keyboard->s.is_pressed) left_stick.y -= 1;
                if (keyboard->a.is_pressed) left_stick.x += 1;
                if (keyboard->d.is_pressed) left_stick.x += -1;
                if (keyboard->left_shift.is_pressed) is_running = 1;
                // float2_normalize_p(&left_stick);
            } else if (deviceMode->value == zox_device_mode_gamepad && ecs_has(world, device_entity, Gamepad)) {
                const Children *zevices = ecs_get(world, device_entity, Children);
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    const ZeviceDisabled *zeviceDisabled = ecs_get(world, zevice_entity, ZeviceDisabled);
                    if (zeviceDisabled->value) continue;
                    const DeviceButtonType *deviceButtonType = ecs_get(world, zevice_entity, DeviceButtonType);
                    if (ecs_has(world, zevice_entity, ZeviceStick)) {
                        if (deviceButtonType->value == zox_device_stick_left) {
                            const ZeviceStick *zeviceStick = ecs_get(world, zevice_entity, ZeviceStick);
                            left_stick.x += zeviceStick->value.x; // joysticks are weird
                            left_stick.y += zeviceStick->value.y;
                        }
                    } else if (ecs_has(world, zevice_entity, ZeviceButton)) {
                        if (deviceButtonType->value == zox_device_button_lb || deviceButtonType->value == zox_device_button_rb) {
                            const ZeviceButton *zeviceButton = ecs_get(world, zevice_entity, ZeviceButton);
                            if (!is_running && devices_get_is_pressed(zeviceButton->value)) is_running = 1;
                        }
                    }
                }
            } else if (deviceMode->value == zox_device_mode_touchscreen && ecs_has(world, device_entity, Touchscreen)) {
                const Children *zevices = ecs_get(world, device_entity, Children);
                for (int k = 0; k < zevices->length; k++) {
                    if (k < fingers_count) continue;
                    ecs_entity_t zevice_entity = zevices->value[k];
                    const ZeviceDisabled *zeviceDisabled = ecs_get(world, zevice_entity, ZeviceDisabled);
                    if (zeviceDisabled->value) continue;
                    if (ecs_has(world, zevice_entity, ZeviceStick)) {
                        const ZeviceStick *zeviceStick = ecs_get(world, zevice_entity, ZeviceStick);
                        left_stick.x -= zeviceStick->value.x;
                        left_stick.y += zeviceStick->value.y;
                    }
                }
            }
        }
        // fixing for this one scenario
        // left_stick.y = -left_stick.x;
        // left_stick.x = 1;
        // left_stick.y = -1;
        if (left_stick.x == 0 && left_stick.y == 0) continue;
        // zoxel_log(" > left_stick %fx%f\n", left_stick.x, left_stick.y);
        float3 movement = { left_stick.x, 0, left_stick.y };
        // const Omega3D *omega3D = ecs_get(world, characterLink->value, Omega3D);
        const Rotation3D *rotation3D = ecs_get(world, characterLink->value, Rotation3D);
        const Velocity3D *velocity3D = ecs_get(world, characterLink->value, Velocity3D);
        Acceleration3D *acceleration3D = ecs_get_mut(world, characterLink->value, Acceleration3D);
        #ifdef zoxel_topdown_camera // now we rotate by camera
            if (ecs_has(world, characterLink->value, CameraLink)) {
                const CameraLink *cameraLink = ecs_get(world, characterLink->value, CameraLink);
                if (cameraLink->value) {
                    const Rotation3D *camera_rotation = ecs_get(world, cameraLink->value, Rotation3D);
                    float4 camera_rotation2 = quaternion_from_euler((float3) { 0, -quaternion_to_euler_y(camera_rotation->value), 0 });
                    if (movement.z == -movement.x) movement.x *= 0.999f; // this hack fixes the rotation
                    movement = float4_rotate_float3(camera_rotation2, movement);
                    movement.y = 0;
                    // movement = float3_normalize(movement);
                    float4 face_direction = quaternion_from_between_vectors(float3_forward, movement);
                    // test rotation
                    Rotation3D *rotation3D2 = ecs_get_mut(world, characterLink->value, Rotation3D);
                    rotation3D2->value = face_direction;
                    ecs_modified(world, characterLink->value, Rotation3D);
                    // todo: rotate towards desired direction
                    // Alpha3D *alpha3D = ecs_get_mut(world, characterLink->value, Alpha3D);
                    // quaternion_rotate_quaternion_p(&alpha3D->value, quaternion);
                    // ecs_modified(world, characterLink->value, Alpha3D);
                    #ifdef zox_debug_player_movement_direction
                        const Position3D *position3D = ecs_get(world, characterLink->value, Position3D);
                        spawn_line3D(world, position3D->value, float3_add(position3D->value, movement), debug_thickness, 34.0);
                        float3 movement2 = float4_rotate_float3(face_direction, (float3) { 0, 0, -1 });
                        spawn_line3D(world, position3D->value, float3_add(position3D->value, movement2), debug_thickness, 34.0);
                        // zoxel_log(" > movement: %fx%fx%f\n", movement.x, movement.y, movement.z);
                        // zoxel_log("     - movement2: %fx%fx%f\n", movement2.x, movement2.y, movement.z);
                        zoxel_log(" > face_direction %fx%fx%fx%f\n", face_direction.x, face_direction.y, face_direction.z, face_direction.w);
                    #endif
                }
            }
        #else
            movement = float4_rotate_float3(rotation3D->value, movement);
        #endif
        if (is_running) {
            movement.x *= run_speed;
            movement.z *= run_speed;
        }
        // if (movement.z < 0) movement.z *= backwards_multiplier;
        float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
        if (float_abs(rotated_velocity.x) < max_delta_velocity.x) acceleration3D->value.x += movement.x * movement_power_x;
        if (float_abs(rotated_velocity.z) < max_delta_velocity.y) acceleration3D->value.z += movement.z * movement_power_z;
        ecs_modified(world, characterLink->value, Acceleration3D);
    }
} zox_declare_system(Player3DMoveSystem)

/*const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
if (float_abs(gamepad->left_stick.value.x) >= joystick_cutoff_buffer) movement.x = gamepad->left_stick.value.x;
if (float_abs(gamepad->left_stick.value.y) >= joystick_cutoff_buffer) movement.z = gamepad->left_stick.value.y;
if (gamepad->lb.is_pressed || gamepad->rb.is_pressed) {
    movement.x *= run_speed;
    movement.z *= run_speed;
}
#ifdef zox_floating_movement
    if (gamepad->a.is_pressed) movement.y = jump_power;
#endif*/

                //if (float_abs(left_stick.x) > joystick_cutoff_buffer) movement.x = left_stick.x;
                //if (float_abs(left_stick.y) > joystick_cutoff_buffer) movement.z = left_stick.y;
                    // movement_rotation = quaternion_rotate(reverse_rotation, movement_rotation);
                    // float euler_y = quaternion_to_euler(movement_rotation).y;
                    // movement_rotation = quaternion_inverse(movement_rotation);
                    // float4 new_rotation = quaternion_from_euler((float3) { 0, euler_y, 0 });
                    // float4 reverse_rotation = (quaternion_from_euler((float3) { 0, 1, 0 })); // quaternion_inverse
                    // float3 movement2 = float4_rotate_float3(reverse_rotation, normalized_movement);
                    // movement = float4_rotate_float3(quaternion_inverse(rotation3D->value), movement);
                    // movement = float4_rotate_float3(camera_rotation->value, movement);
                    /*
                    float3 camera_euler = quaternion_to_euler(camera_rotation->value);
                    camera_euler.x = 0;
                    camera_euler.z = 0;
                    float4 camera_rotation2 = quaternion_from_euler(camera_euler);  // the y axis
                    */
                    
                    //movement = float4_rotate_float3(float4_inverse(rotation3D->value), movement);
                    //movement = float4_rotate_float3(camera_rotation->value, float3_multiply_float(movement, -1.0f));
                    // set character to rotate here too, towards the direction
                    // float4 quaternion = mouse_delta_to_rotation(euler.x, euler.y);
                    // float4 quaternion = quaternion_from_euler(float3_normalize(movement));
                    
                    // quaternion_rotate_quaternion_p(&movement_rotation, quaternion_from_euler((float3) { 90 * degreesToRadians, 90 * degreesToRadians, 0 }));
                    // quaternion_rotate_quaternion_p(&movement_rotation, quaternion_from_euler((float3) { 0, 90 * degreesToRadians, 0 }));
                    // zoxel_log("     > normalized_movement: %fx%fx%f\n", normalized_movement.x, normalized_movement.y, normalized_movement.z);
                    // zoxel_log("     > euler_y: %f\n", euler_y);
                    // rotate towards looking direction
                        // float3 direction_vector = float4_rotate_float3(camera_rotation2, (float3) { 0, 1, 0 }); // 
                        // float4 quaternion2 = quaternion_rotate(quaternion_inverse(rotation3D->value), quaternion);
                        /*float3 direction_vector = quaternion_to_euler(movement_rotation);
                        direction_vector.y = 0;
                        direction_vector = float3_normalize(direction_vector);*/
                    // float4 movement_rotation = quaternion_from_normal(movement); // quaternion_from_euler(movement);
                    // float4 movement_rotation = quaternion_from_between_vectors(float3_zero, movement);
                /*#ifdef zox_floating_movement
                    if (keyboard->space.is_pressed) movement.y = jump_power;
                #endif*/