const double jump_power = 12.0;
const double movement_power_x = 6; // 16;
const double movement_power_z = 9; // 24;
const float2 max_velocity = { 60 * 60, 160 * 60 };
const double run_speed = 1.6;
const float backwards_multiplier = 0.7f;
// #define zox_floating_movement
// todo: get rotated velocity to test max

void Player3DMoveSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    double delta_time = zox_delta_time;
    float2 max_delta_velocity = max_velocity;
    max_delta_velocity.x *= delta_time;
    max_delta_velocity.y *= delta_time;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const CharacterLink *characterLinks = ecs_field(it, CharacterLink, 3);
    for (int i = 0; i < it->count; i++) {
        const CharacterLink *characterLink = &characterLinks[i];
        if (characterLink->value == 0) continue;
        const DisableMovement *disableMovement = ecs_get(world, characterLink->value, DisableMovement);
        if (disableMovement->value) continue;
        float3 movement = { 0, 0, 0 };
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->w.is_pressed) movement.z += 1;
                if (keyboard->s.is_pressed) movement.z -= 1;
                if (keyboard->a.is_pressed) movement.x += 1;
                if (keyboard->d.is_pressed) movement.x += -1;
                if (keyboard->left_shift.is_pressed) {
                    movement.x *= run_speed;
                    movement.z *= run_speed;
                }
                #ifdef zox_floating_movement
                    if (keyboard->space.is_pressed) movement.y = jump_power;
                #endif
            } else if (ecs_has(world, device_entity, Gamepad)) {
                float2 left_stick = float2_zero;
                unsigned char is_run = 0;
                const Children *zevices = ecs_get(world, device_entity, Children);
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    const ZeviceDisabled *zeviceDisabled = ecs_get(world, zevice_entity, ZeviceDisabled);
                    if (zeviceDisabled->value) continue;
                    const DeviceButtonType *deviceButtonType = ecs_get(world, zevice_entity, DeviceButtonType);
                    if (ecs_has(world, zevice_entity, DeviceStick)) {
                        if (deviceButtonType->value == zox_device_stick_left) {
                            const DeviceStick *deviceStick = ecs_get(world, zevice_entity, DeviceStick);
                            left_stick = deviceStick->value;
                        }
                    } else if (ecs_has(world, zevice_entity, DeviceButton)) {
                        if (deviceButtonType->value == zox_device_button_lb || deviceButtonType->value == zox_device_button_rb) {
                            const DeviceButton *deviceButton = ecs_get(world, zevice_entity, DeviceButton);
                            if (!is_run && devices_get_is_pressed(deviceButton->value)) is_run = 1;
                        }
                    }
                }
                if (float_abs(left_stick.x) > joystick_cutoff_buffer) movement.x = left_stick.x;
                if (float_abs(left_stick.y) > joystick_cutoff_buffer) movement.z = left_stick.y;
                if (is_run) {
                    movement.x *= run_speed;
                    movement.z *= run_speed;
                }
            }
        }
        if (movement.x == 0 && movement.y == 0 && movement.z == 0) continue;
        if (movement.z < 0) movement.z *= backwards_multiplier;
        // const Omega3D *omega3D = ecs_get(world, characterLink->value, Omega3D);
        const Rotation3D *rotation3D = ecs_get(world, characterLink->value, Rotation3D);
        const Velocity3D *velocity3D = ecs_get(world, characterLink->value, Velocity3D);
        Acceleration3D *acceleration3D = ecs_get_mut(world, characterLink->value, Acceleration3D);
        float3 rotated_movement = float4_rotate_float3(rotation3D->value, movement);
        float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
        if (float_abs(rotated_velocity.x) < max_delta_velocity.x) acceleration3D->value.x += rotated_movement.x * movement_power_x;
        if (float_abs(rotated_velocity.z) < max_delta_velocity.y) acceleration3D->value.z += rotated_movement.z * movement_power_z;
        acceleration3D->value.y += rotated_movement.y;
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
