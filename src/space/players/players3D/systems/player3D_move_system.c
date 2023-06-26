const double jump_power = 12.0;
const double movement_power_x = 12; // 16;
const double movement_power_z = 16; // 24;
const float2 max_velocity = { 60 * 60, 160 * 60 };
const double run_speed = 1.3;
const float backwards_multiplier = 0.7f;
// #define zox_floating_movement

void Player3DMoveSystem(ecs_iter_t *it) {
    ecs_query_t *playerCharacterQuery = it->ctx;
    ecs_iter_t characters_iter = ecs_query_iter(it->world, playerCharacterQuery);
    ecs_query_next(&characters_iter);
    if (characters_iter.count == 0) return;
    ecs_world_t *world = it->world;
    double delta_time = zox_delta_time;
    float2 max_delta_velocity = max_velocity;
    max_delta_velocity.x *= delta_time;
    max_delta_velocity.y *= delta_time;
    const DeviceLinks *deviceLinkss = ecs_field(it, DeviceLinks, 2);
    const CharacterLink *characterLinks = ecs_field(it, CharacterLink, 3);
    Acceleration3D *acceleration3Ds = ecs_field(&characters_iter, Acceleration3D, 2);
    const Velocity3D *velocity3Ds = ecs_field(&characters_iter, Velocity3D, 3);
    const DisableMovement *disableMovements = ecs_field(&characters_iter, DisableMovement, 4);
    const Rotation3D *rotation3Ds = ecs_field(&characters_iter, Rotation3D, 5);
    for (int i = 0; i < it->count; i++) {
        const CharacterLink *characterLink = &characterLinks[i];
        if (characterLink->value == 0) continue;
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        float3 movement = { 0, 0, 0 };
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
                const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                if (float_abs(gamepad->left_stick.value.x) >= joystick_buffer) movement.x = gamepad->left_stick.value.x;
                if (float_abs(gamepad->left_stick.value.y) >= joystick_buffer) movement.z = gamepad->left_stick.value.y;
                if (gamepad->lb.is_pressed || gamepad->rb.is_pressed) {
                    movement.x *= run_speed;
                    movement.z *= run_speed;
                }
                #ifdef zox_floating_movement
                    if (gamepad->a.is_pressed) movement.y = jump_power;
                #endif
            }
        }
        if (movement.x == 0 && movement.y == 0 && movement.z == 0) continue;
        if (movement.z < 0) movement.z *= backwards_multiplier;
        for (int j = 0; j < characters_iter.count; j++) {
            if (characters_iter.entities[j] != characterLink->value) continue;
            const DisableMovement *disableMovement = &disableMovements[j];
            if (disableMovement->value) continue;
            const Rotation3D *rotation3D = &rotation3Ds[j];
            const Velocity3D *velocity3D = &velocity3Ds[j];
            Acceleration3D *acceleration3D = &acceleration3Ds[j];
            float3 rotated_movement = float4_rotate_float3(rotation3D->value, movement);
            float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
            if (float_abs(rotated_velocity.x) < max_delta_velocity.x) acceleration3D->value.x += rotated_movement.x * movement_power_x;
            if (float_abs(rotated_velocity.z) < max_delta_velocity.y) acceleration3D->value.z += rotated_movement.z * movement_power_z;
            acceleration3D->value.y += rotated_movement.y;
            break;
        }
    }
} zox_declare_system(Player3DMoveSystem)

// do this until I get a player -> deviceLinks setup going
// todo: get rotated velocity to test max
// todo: Link directly to player characters from player