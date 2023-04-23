const double jump_power = 4.0;
const double movement_power = 32;
const double movement_power_x = 24;
const double movement_power_z = 32;
const float2 max_velocity = { 60 * 60, 160 * 60 };
const double run_speed = 1.6;
const float backwards_multiplier = 0.6f;
// todo: Link directly to player characters from player
// do this until I get a player -> deviceLinks setup going
// todo: get rotated velocity to test max

void Player3DMoveSystem(ecs_iter_t *it) {
    ecs_query_t *playerCharacterQuery = it->ctx;
    ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacterQuery);
    ecs_query_next(&playerCharacterIterator);
    if (playerCharacterIterator.count == 0) {
        return;
    }
    double delta_time = zoxel_delta_time;
    float2 max_delta_velocity = max_velocity;
    max_delta_velocity.x *= delta_time;
    max_delta_velocity.y *= delta_time;
    Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    Acceleration3D *acceleration3Ds = ecs_field(&playerCharacterIterator, Acceleration3D, 2);
    const Velocity3D *velocity3Ds = ecs_field(&playerCharacterIterator, Velocity3D, 3);
    const DisableMovement *disableMovements = ecs_field(&playerCharacterIterator, DisableMovement, 4);
    const Rotation3D *rotation3Ds = ecs_field(&playerCharacterIterator, Rotation3D, 5);
    for (int i = 0; i < it->count; i++) {
        const Keyboard *keyboard = &keyboards[i];
        unsigned char is_backwards = 0;
        float3 movement = { 0, 0, 0 };
        if (keyboard->w.is_pressed) {
            movement.z += -1;
        }
        if (keyboard->s.is_pressed) {
            movement.z += 1;
            is_backwards = 1;
        }
        if (keyboard->a.is_pressed) {
            movement.x += -1;
        }
        if (keyboard->d.is_pressed) {
            movement.x += 1;
        }
        if (keyboard->left_shift.is_pressed) {
            movement.x *= run_speed;
            movement.z *= run_speed;
        }
        if (is_backwards) {
            movement.z *= backwards_multiplier;
        }
        if (keyboard->space.is_pressed) {
            movement.y = jump_power;
        }
        if (!(movement.x == 0 && movement.y == 0 && movement.z == 0)) {
            //movement.x *= movement_power;
            //movement.z *= movement_power;
            for (int j = 0; j < playerCharacterIterator.count; j++) {
                const DisableMovement *disableMovement = &disableMovements[j];
                if (disableMovement->value) {
                    continue;
                }
                const Rotation3D *rotation3D = &rotation3Ds[j];
                const Velocity3D *velocity3D = &velocity3Ds[j];
                Acceleration3D *acceleration3D = &acceleration3Ds[j];
                float3 rotated_movement = float4_rotate_float3(rotation3D->value, movement);
                rotated_movement.x *= movement_power_x;
                rotated_movement.z *= movement_power_z;
                float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
                if (rotated_movement.x > 0 && rotated_velocity.x < max_delta_velocity.x) {
                    acceleration3D->value.x += rotated_movement.x;
                } else if (rotated_movement.x < 0 && rotated_velocity.x > -max_delta_velocity.x) {
                    acceleration3D->value.x += rotated_movement.x;
                }
                if (rotated_movement.z > 0 && rotated_velocity.z < max_delta_velocity.y) {
                    acceleration3D->value.z += rotated_movement.z;
                } else if (rotated_movement.z < 0 && rotated_velocity.z > -max_delta_velocity.y) {
                    acceleration3D->value.z += rotated_movement.z;
                }
                acceleration3D->value.y += rotated_movement.y;
            }
        }
    }
}
zoxel_declare_system(Player3DMoveSystem)

void Player3DMoveSystem2(ecs_iter_t *it) {
    ecs_query_t *playerCharacterQuery = it->ctx;
    ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacterQuery);
    ecs_query_next(&playerCharacterIterator);
    if (playerCharacterIterator.count == 0) {
        return;
    }
    double delta_time = zoxel_delta_time;
    float2 max_delta_velocity = max_velocity;
    Gamepad *gamepads = ecs_field(it, Gamepad, 1);
    Acceleration3D *acceleration3Ds = ecs_field(&playerCharacterIterator, Acceleration3D, 2);
    const Velocity3D *velocity3Ds = ecs_field(&playerCharacterIterator, Velocity3D, 3);
    const DisableMovement *disableMovements = ecs_field(&playerCharacterIterator, DisableMovement, 4);
    const Rotation3D *rotation3Ds = ecs_field(&playerCharacterIterator, Rotation3D, 5);
    for (int i = 0; i < it->count; i++) {
        const Gamepad *gamepad = &gamepads[i];
        float3 movement = { 0, 0, 0 };
        unsigned char is_backwards = 0;
        if (gamepad->left_stick.value.x < -joystick_buffer) {
            movement.x = gamepad->left_stick.value.x;
        } else if (gamepad->left_stick.value.x > joystick_buffer) {
            movement.x = gamepad->left_stick.value.x;
        }
        if (gamepad->left_stick.value.y < -joystick_buffer) {
            movement.z = gamepad->left_stick.value.y;
        } else if (gamepad->left_stick.value.y > joystick_buffer) {
            movement.z = gamepad->left_stick.value.y;
            is_backwards = 1;
        }
        if (gamepad->lb.is_pressed || gamepad->rb.is_pressed) {
            movement.x *= run_speed;
            movement.z *= run_speed;
        }
        if (is_backwards) {
            movement.z *= backwards_multiplier;
        }
        if (gamepad->a.is_pressed) {
            movement.y = jump_power;
        }
        if (!(movement.x == 0 && movement.y == 0 && movement.z == 0)) {
            //movement.x *= movement_power;
            //movement.z *= movement_power;
            for (int j = 0; j < playerCharacterIterator.count; j++) {
                const DisableMovement *disableMovement = &disableMovements[j];
                if (disableMovement->value) {
                    continue;
                }
                const Rotation3D *rotation3D = &rotation3Ds[j];
                const Velocity3D *velocity3D = &velocity3Ds[j];
                Acceleration3D *acceleration3D = &acceleration3Ds[j];
                float3 rotated_movement = float4_rotate_float3(rotation3D->value, movement);
                rotated_movement.x *= movement_power_x;
                rotated_movement.z *= movement_power_z;
                float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
                if (rotated_movement.x > 0 && rotated_velocity.x < max_delta_velocity.x) {
                    acceleration3D->value.x += rotated_movement.x;
                } else if (rotated_movement.x < 0 && rotated_velocity.x > -max_delta_velocity.x) {
                    acceleration3D->value.x += rotated_movement.x;
                }
                if (rotated_movement.z > 0 && rotated_velocity.z < max_delta_velocity.y) {
                    acceleration3D->value.z += rotated_movement.z;
                } else if (rotated_movement.z < 0 && rotated_velocity.z > -max_delta_velocity.y) {
                    acceleration3D->value.z += rotated_movement.z;
                }
                acceleration3D->value.y += rotated_movement.y;
            }
        }
    }
}
zoxel_declare_system(Player3DMoveSystem2)