const double rotate_power = 0.09;
const double max_rotate_speed = 0.23;
const double rotate_power_mouse = 0.008;

float4 mouse_delta_to_rotation(float deltaX, float deltaY) {
    float4 output = quaternion_identity;
    output.x = deltaX;
    output.y = deltaY;
    // quaternion_normalize(&output);
    return output;
}

void Player3DRotateSystem(ecs_iter_t *it) {
    ecs_query_t *playerCharacterQuery = it->ctx;
    ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacterQuery);
    ecs_query_next(&playerCharacterIterator);
    if (playerCharacterIterator.count == 0) {
        return;
    }
    Mouse *mouses = ecs_field(it, Mouse, 1);
    Alpha3D *alpha3Ds = ecs_field(&playerCharacterIterator, Alpha3D, 2);
    const Omega3D *omega3Ds = ecs_field(&playerCharacterIterator, Omega3D, 3);
    const DisableMovement *disableMovements = ecs_field(&playerCharacterIterator, DisableMovement, 4);
    for (int i = 0; i < it->count; i++) {
        const Mouse *mouse = &mouses[i];
        float3 euler = { 0, -mouse->delta.x }; // * 0.12f };
        if (!(euler.x == 0 && euler.y == 0)) {
            // euler.x *= rotate_power;
            /*if (euler.y > 0) {
                euler.y = rotate_power_mouse;
            } else {
                euler.y = -rotate_power_mouse;
            }*/
            euler.y *= rotate_power_mouse;
            float4 quaternion = mouse_delta_to_rotation(euler.x, euler.y);
            for (int j = 0; j < playerCharacterIterator.count; j++) {
                const DisableMovement *disableMovement = &disableMovements[j];
                if (disableMovement->value) {
                    continue;
                }
                const Omega3D *omega3D = &omega3Ds[j];
                if ((euler.y > 0 && quaternion_to_euler_y(omega3D->value) < max_rotate_speed) ||
                    euler.y < 0 && quaternion_to_euler_y(omega3D->value) > -max_rotate_speed) {
                    Alpha3D *alpha3D = &alpha3Ds[j];
                    quaternion_rotate_quaternion_p(&alpha3D->value, quaternion);
                }
            }
        }
    }
}
zoxel_declare_system(Player3DRotateSystem)

void Player3DRotateSystem2(ecs_iter_t *it) {
    ecs_query_t *playerCharacterQuery = it->ctx;
    ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacterQuery);
    ecs_query_next(&playerCharacterIterator);
    if (playerCharacterIterator.count == 0) {
        return;
    }
    Gamepad *gamepads = ecs_field(it, Gamepad, 1);
    Alpha3D *alpha3Ds = ecs_field(&playerCharacterIterator, Alpha3D, 2);
    const Omega3D *omega3Ds = ecs_field(&playerCharacterIterator, Omega3D, 3);
    const DisableMovement *disableMovements = ecs_field(&playerCharacterIterator, DisableMovement, 4);
    for (int i = 0; i < it->count; i++) {
        const Gamepad *gamepad = &gamepads[i];
        float3 euler = { 0, 0 };
        if (gamepad->right_stick.value.x < -joystick_buffer) {
            euler.y = -gamepad->right_stick.value.x;
        } else if (gamepad->right_stick.value.x > joystick_buffer) {
            euler.y = -gamepad->right_stick.value.x;
        }
        if (!(euler.x == 0 && euler.y == 0)) {
            // euler.x *= rotate_power;
            euler.y *= rotate_power;
            float4 quaternion = mouse_delta_to_rotation(euler.x, euler.y);
            for (int j = 0; j < playerCharacterIterator.count; j++) {
                const DisableMovement *disableMovement = &disableMovements[j];
                if (disableMovement->value) {
                    continue;
                }
                const Omega3D *omega3D = &omega3Ds[j];
                if ((euler.y > 0 && quaternion_to_euler_y(omega3D->value) < max_rotate_speed) ||
                    euler.y < 0 && quaternion_to_euler_y(omega3D->value) > -max_rotate_speed) {
                    Alpha3D *alpha3D = &alpha3Ds[j];
                    quaternion_rotate_quaternion_p(&alpha3D->value, quaternion);
                }
            }
        }
    }
}
zoxel_declare_system(Player3DRotateSystem2)