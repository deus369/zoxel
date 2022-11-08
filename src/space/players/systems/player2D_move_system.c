//! Adds acceleration based on user input.
/**
 * Only affects player characters that arn't disabled (DisableMovement).
*/
void Player2DMoveSystem(ecs_iter_t *it)
{
    double movementPower = 2.8f;
    const float2 maxVelocity = { 12.6f, 12.6f };
    ecs_query_t *playerCharacterQuery = it->ctx;
    ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacterQuery);
    ecs_query_next(&playerCharacterIterator);
    if (playerCharacterIterator.count == 0)
    {
        return;
    }
    Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    Acceleration2D *acceleration2Ds = ecs_field(&playerCharacterIterator, Acceleration2D, 2);
    const Velocity2D *velocity2Ds = ecs_field(&playerCharacterIterator, Velocity2D, 3);
    const DisableMovement *disableMovements = ecs_field(&playerCharacterIterator, DisableMovement, 4);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        float2 movement = { 0, 0 };
        if (keyboard->w.isPressed)
        {
            movement.y = 1;
        }
        if (keyboard->s.isPressed)
        {
            movement.y = -1;
        }
        if (keyboard->a.isPressed)
        {
            movement.x = -1;
        }
        if (keyboard->d.isPressed)
        {
            movement.x = 1;
        }
        if (!(movement.x == 0 && movement.y == 0))
        {
            movement.x *= movementPower;
            movement.y *= movementPower;
            //! \todo Link directly to player characters from player.
            for (int j = 0; j < playerCharacterIterator.count; j++)
            {
                const DisableMovement *disableMovement = &disableMovements[j];
                if (disableMovement->value)
                {
                    continue;
                }
                const Velocity2D *velocity2D = &velocity2Ds[j];
                Acceleration2D *acceleration2D = &acceleration2Ds[j];
                if (movement.x > 0 && velocity2D->value.x < maxVelocity.x)
                {
                    acceleration2D->value.x += movement.x;
                }
                else if (movement.x < 0 && velocity2D->value.x > -maxVelocity.x)
                {
                    acceleration2D->value.x += movement.x;
                }
                if (movement.y > 0 && velocity2D->value.y < maxVelocity.y)
                {
                    acceleration2D->value.y += movement.y;
                }
                else if (movement.y < 0 && velocity2D->value.y > -maxVelocity.y)
                {
                    acceleration2D->value.y += movement.y;
                }
            }
        }
    }
}
ECS_SYSTEM_DECLARE(Player2DMoveSystem);