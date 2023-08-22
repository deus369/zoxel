void Player2DMoveSystem(ecs_iter_t *it) {
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
        if (!ecs_has(world, characterLink->value, Character2D)) continue;
        const DisableMovement *disableMovement = ecs_get(world, characterLink->value, DisableMovement);
        if (disableMovement->value) continue;
        float2 movement = { 0, 0 };
        const DeviceLinks *deviceLinks = &deviceLinkss[i];
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (ecs_has(world, device_entity, Keyboard)) {
                const Keyboard *keyboard = ecs_get(world, device_entity, Keyboard);
                if (keyboard->a.is_pressed) movement.x = -1;
                if (keyboard->d.is_pressed) movement.x = 1;
                if (keyboard->w.is_pressed) movement.y = 1;
                if (keyboard->s.is_pressed) movement.y = -1;
                if (keyboard->left_shift.is_pressed) {
                    movement.x *= run_speed;
                    movement.y *= run_speed;
                }
            } else if (ecs_has(world, device_entity, Gamepad)) {
                const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                if (float_abs(gamepad->left_stick.value.x) >= joystick_cutoff_buffer) movement.x = gamepad->left_stick.value.x;
                if (float_abs(gamepad->left_stick.value.y) >= joystick_cutoff_buffer) movement.y = gamepad->left_stick.value.y;
                if (gamepad->lb.is_pressed || gamepad->rb.is_pressed) {
                    movement.x *= run_speed;
                    movement.y *= run_speed;
                }
            }
        }
        if (movement.x == 0 && movement.y == 0) continue;
        const Velocity2D *velocity2D = ecs_get(world, characterLink->value, Velocity2D);
        Acceleration2D *acceleration2D = ecs_get_mut(world, characterLink->value, Acceleration2D);
        float2 delta_movement = movement;
        float2 check_velocity = velocity2D->value;
        if (float_abs(check_velocity.x) < max_delta_velocity.x) acceleration2D->value.x += delta_movement.x * movement_power_x;
        if (float_abs(check_velocity.y) < max_delta_velocity.y) acceleration2D->value.y += delta_movement.y * movement_power_z;
        ecs_modified(world, characterLink->value, Acceleration2D);
    }
} zox_declare_system(Player2DMoveSystem);

// const double movementPower = 2.8f;
// const float2 maxVelocity = { 12.6f, 12.6f };
/*if (!(movement.x == 0 && movement.y == 0)) {
    movement.x *= movementPower;
    movement.y *= movementPower;
    //! \todo Link directly to player characters from player.
    for (int j = 0; j < playerCharacterIterator.count; j++) {
        const DisableMovement *disableMovement = &disableMovements[j];
        if (disableMovement->value) {
            continue;
        }
        const Velocity2D *velocity2D = &velocity2Ds[j];
        Acceleration2D *acceleration2D = &acceleration2Ds[j];
        if (movement.x > 0 && velocity2D->value.x < maxVelocity.x) {
            acceleration2D->value.x += movement.x;
        } else if (movement.x < 0 && velocity2D->value.x > -maxVelocity.x) {
            acceleration2D->value.x += movement.x;
        }
        if (movement.y > 0 && velocity2D->value.y < maxVelocity.y) {
            acceleration2D->value.y += movement.y;
        } else if (movement.y < 0 && velocity2D->value.y > -maxVelocity.y) {
            acceleration2D->value.y += movement.y;
        }
    }
}*/
/*ecs_query_t *playerCharacterQuery = it->ctx;
ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacterQuery);
ecs_query_next(&playerCharacterIterator);
if (playerCharacterIterator.count == 0) return;*/
// Keyboard *keyboards = ecs_field(it, Keyboard, 1);
/*Acceleration2D *acceleration2Ds = ecs_field(&playerCharacterIterator, Acceleration2D, 2);
const Velocity2D *velocity2Ds = ecs_field(&playerCharacterIterator, Velocity2D, 3);
const DisableMovement *disableMovements = ecs_field(&playerCharacterIterator, DisableMovement, 4);*/