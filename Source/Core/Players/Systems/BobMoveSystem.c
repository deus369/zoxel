
void BobMoveSystem(ecs_iter_t *it);
ECS_SYSTEM_DECLARE(BobMoveSystem);

//! Called in ecs updates
void BobMoveSystem(ecs_iter_t *it)
{
    const float movementPower = 0.4f;
    double deltaTime = (double) it->delta_time;
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
            movement.x *= deltaTime * movementPower;
            movement.y *= deltaTime * movementPower;
            for (int j = 0; j < bobIter.count; j++)
            {
                // printf("Bob Moving %lu \n", bobIter.entities[j]);
                Acceleration2D *acceleration2D = &acceleration2Ds[j];
                acceleration2D->value.x = movement.x;
                acceleration2D->value.y = movement.y;
            }
        }
    }
}


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