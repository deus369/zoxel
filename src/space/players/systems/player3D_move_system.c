//! Adds acceleration based on user input.
/**
 * Only affects player characters that arn't disabled (DisableMovement).
*/
void Player3DMoveSystem(ecs_iter_t *it) {
    const double movementPower = 1.8f;
    const double jump_power = 4.0;
    const float2 maxVelocity = { 12.6f, 12.6f };
    ecs_query_t *playerCharacterQuery = it->ctx;
    ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacterQuery);
    ecs_query_next(&playerCharacterIterator);
    if (playerCharacterIterator.count == 0) {
        return;
    }
    Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    Acceleration3D *acceleration3Ds = ecs_field(&playerCharacterIterator, Acceleration3D, 2);
    const Velocity3D *velocity3Ds = ecs_field(&playerCharacterIterator, Velocity3D, 3);
    const DisableMovement *disableMovements = ecs_field(&playerCharacterIterator, DisableMovement, 4);
    const Rotation3D *rotation3Ds = ecs_field(&playerCharacterIterator, Rotation3D, 5);
    for (int i = 0; i < it->count; i++) {
        const Keyboard *keyboard = &keyboards[i];
        float3 movement = { 0, 0, 0 };
        if (keyboard->w.is_pressed) {
            movement.z = -1;
        }
        if (keyboard->s.is_pressed) {
            movement.z = 1;
        }
        if (keyboard->a.is_pressed) {
            movement.x = -1;
        }
        if (keyboard->d.is_pressed) {
            movement.x = 1;
        }
        if (keyboard->space.is_pressed) {
            movement.y = jump_power;
        }
        if (!(movement.x == 0 && movement.y == 0 && movement.z == 0)) {
            movement.x *= movementPower;
            movement.z *= movementPower;
            //! \todo Link directly to player characters from player.
            for (int j = 0; j < playerCharacterIterator.count; j++) {
                const DisableMovement *disableMovement = &disableMovements[j];
                if (disableMovement->value) {
                    continue;
                }
                const Rotation3D *rotation3D = &rotation3Ds[j];
                const Velocity3D *velocity3D = &velocity3Ds[j];
                Acceleration3D *acceleration3D = &acceleration3Ds[j];
                float3 rotated_movement = float4_rotate_float3(rotation3D->value, movement);
                float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
                // todo: get rotated velocity to test max
                if (rotated_movement.x > 0 && rotated_velocity.x < maxVelocity.x) {
                    acceleration3D->value.x += rotated_movement.x;
                } else if (rotated_movement.x < 0 && rotated_velocity.x > -maxVelocity.x) {
                    acceleration3D->value.x += rotated_movement.x;
                }
                acceleration3D->value.y += rotated_movement.y;
                if (rotated_movement.z > 0 && rotated_velocity.z < maxVelocity.y) {
                    acceleration3D->value.z += rotated_movement.z;
                } else if (rotated_movement.z < 0 && rotated_velocity.z > -maxVelocity.y) {
                    acceleration3D->value.z += rotated_movement.z;
                }
                /*if (movement.y > 0 && velocity3D->value.y < maxVelocity.y) {
                    acceleration3D->value.y += movement.y;
                } else if (movement.y < 0 && velocity3D->value.y > -maxVelocity.y) {
                    acceleration3D->value.y += movement.y;
                }*/
            }
        }
    }
}
zoxel_declare_system(Player3DMoveSystem)