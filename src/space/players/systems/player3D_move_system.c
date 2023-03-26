//! Adds acceleration based on user input.
/**
 * Only affects player characters that arn't disabled (DisableMovement).
*/
void Player3DMoveSystem(ecs_iter_t *it) {
    const double movementPower = 2.8f;
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
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        float2 movement = { 0, 0 };
        if (keyboard->w.is_pressed) {
            movement.y = 1;
        }
        if (keyboard->s.is_pressed) {
            movement.y = -1;
        }
        if (keyboard->a.is_pressed) {
            movement.x = -1;
        }
        if (keyboard->d.is_pressed) {
            movement.x = 1;
        }
        if (!(movement.x == 0 && movement.y == 0)) {
            movement.x *= movementPower;
            movement.y *= movementPower;
            //! \todo Link directly to player characters from player.
            for (int j = 0; j < playerCharacterIterator.count; j++) {
                const DisableMovement *disableMovement = &disableMovements[j];
                if (disableMovement->value) {
                    continue;
                }
                const Velocity3D *velocity3D = &velocity3Ds[j];
                Acceleration3D *acceleration3D = &acceleration3Ds[j];
                if (movement.x > 0 && velocity3D->value.x < maxVelocity.x) {
                    acceleration3D->value.x += movement.x;
                } else if (movement.x < 0 && velocity3D->value.x > -maxVelocity.x) {
                    acceleration3D->value.x += movement.x;
                }
                if (movement.y > 0 && velocity3D->value.y < maxVelocity.y) {
                    acceleration3D->value.y += movement.y;
                } else if (movement.y < 0 && velocity3D->value.y > -maxVelocity.y) {
                    acceleration3D->value.y += movement.y;
                }
            }
        }
    }
}
zoxel_declare_system(Player3DMoveSystem)