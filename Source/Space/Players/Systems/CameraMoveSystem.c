//! Called in ecs updates
void CameraMoveSystem(ecs_iter_t *it)
{
    double deltaTime = (double) (it->delta_time);
    double movementPower = 0.006 * 100 * deltaTime; // 2.8f; // * deltaTime;
    float rotatePower = 0.25f * 100 * deltaTime;
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
    Position *positions = ecs_field(&bobIter, Position, 2);
    Rotation *rotations = ecs_field(&bobIter, Rotation, 3);
    //Acceleration *accelerations = ecs_field(&bobIter, Acceleration, 2);
    //const Velocity *velocitys = ecs_field(&bobIter, Velocity, 3);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        float3 movement = { 0, 0, 0 };
        if (keyboard->left.isPressed)
        {
            movement.x = -1;
        }
        if (keyboard->right.isPressed)
        {
            movement.x = 1;
        }
        if (keyboard->up.isPressed)
        {
            movement.y = 1;
        }
        if (keyboard->down.isPressed)
        {
            movement.y = -1;
        }
        if (keyboard->q.isPressed)
        {
            movement.z = -1;
        }
        if (keyboard->e.isPressed)
        {
            movement.z = 1;
        }
        if (!(movement.x == 0 && movement.y == 0 && movement.z == 0))
        {
            // printf("Bob Accel %f x %f \n", movement.x, movement.y);
            movement.x *= movementPower;
            movement.y *= movementPower;
            movement.z *= movementPower;
            for (int j = 0; j < bobIter.count; j++)
            {
                Position *position = &positions[j];
                position->value.x += movement.x;
                position->value.y += movement.y;
                position->value.z += movement.z;
            }
        }
        float3 rotate = { 0, 0, 0 };
        if (keyboard->j.isPressed)
        {
            rotate.x = -1;
        }
        if (keyboard->l.isPressed)
        {
            rotate.x = 1;
        }
        if (keyboard->i.isPressed)
        {
            rotate.y = 1;
        }
        if (keyboard->k.isPressed)
        {
            rotate.y = -1;
        }
        if (keyboard->u.isPressed)
        {
            rotate.z = -1;
        }
        if (keyboard->o.isPressed)
        {
            rotate.z = 1;
        }
        if (!(rotate.x == 0 && rotate.y == 0 && rotate.z == 0))
        {
            rotate.x *= rotatePower;
            rotate.y *= rotatePower;
            rotate.z *= rotatePower;
            rotate.x *= degreesToRadians;
            rotate.y *= degreesToRadians;
            rotate.z *= degreesToRadians;
            float3 rotate2 = { rotate.x, rotate.z, -rotate.y };
            // rotate2.z is x
            float4 rotate3 = quaternion_from_euler(rotate2);
            // printf("rotate: %fx%f\n", rotate.x, rotate.y);
            for (int j = 0; j < bobIter.count; j++)
            {
                Rotation *rotation = &rotations[j];
                rotation->value = quaternion_rotate(rotate3, rotation->value);
            }
        }
    }
}
ECS_SYSTEM_DECLARE(CameraMoveSystem);


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

                // printf("Bob Moving %lu \n", bobIter.entities[j]);
                /*const Velocity *velocity2D = &velocitys[j];
                Acceleration *acceleration = &accelerations[j];
                if (movement.x > 0 && velocity2D->value.x < maxVelocity.x)
                {
                    acceleration->value.x += movement.x;
                }
                else if (movement.x < 0 && velocity2D->value.x > -maxVelocity.x)
                {
                    acceleration->value.x += movement.x;
                }
                if (movement.y > 0 && velocity2D->value.y < maxVelocity.y)
                {
                    acceleration->value.y += movement.y;
                }
                else if (movement.y < 0 && velocity2D->value.y > -maxVelocity.y)
                {
                    acceleration->value.y += movement.y;
                }*/