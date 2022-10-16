float math_abs(float input)
{
    if (input < 0)
    {
        return -input;
    }
    else
    {
        return input;
    }
}

//! Called in ecs updates
void Player2DMoveSystem(ecs_iter_t *it)
{
    // double deltaTime = (double) (it->delta_time);
    double movementPower = 2.8f; // * deltaTime;
    // const float2 maxVelocity = { 0.12f, 0.12f };
    const float2 maxVelocity = { 12.6f, 12.6f };
    // printf("deltaTime! %f\n", deltaTime);
    ecs_query_t *bobQuery = it->ctx;
    if (!bobQuery)
    {
        printf("[404; bobQuery is void]\n");
        return;
    }
    ecs_iter_t bobIter = ecs_query_iter(it->world, bobQuery);
    ecs_query_next(&bobIter);
    if (bobIter.count == 0)
    {
        // printf("[404; Bob Not Found]\n");
        return;
    }
    // printf("Bobs Found [%i]\n", bobIter.count);
    Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    Acceleration2D *acceleration2Ds = ecs_field(&bobIter, Acceleration2D, 2);
    const Velocity2D *velocity2Ds = ecs_field(&bobIter, Velocity2D, 3);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        float2 movement = { 0, 0 };
        // Move Bob Up!
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
            // printf("Bob Accel %f x %f \n", movement.x, movement.y);
            movement.x *= movementPower;
            movement.y *= movementPower;
            for (int j = 0; j < bobIter.count; j++)
            {
                // printf("Bob Moving %lu \n", bobIter.entities[j]);
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


/*printf("Bob is moving: %fx%f %lu \n", movement.x, movement.y, bobPlayer);
Acceleration2D *acceleration2D = ecs_get_mut(it->world, bobPlayer, Acceleration2D);
acceleration2D->value.x += movement.x * deltaTime * movementPower;
acceleration2D->value.y += movement.y * deltaTime * movementPower;
ecs_modified(it->world, bobPlayer, Acceleration2D);*/


//ecs_entity_t *bobEntitys = ecs_field_id(bobIt, 1);
//ecs_entity_t bobEntity = bobEntitys[0];
// Acceleration2D *acceleration2Ds = ecs_field(it, Acceleration2D, 1);

/*ecs_query_t *bobQuery = ecs_query(it->world, {
    .filter.terms = {
        { .id = ecs_id(Bob) }
    }
});*/
/**/
// ecs_entity_t bobPlayer = bobIt.entities[0];