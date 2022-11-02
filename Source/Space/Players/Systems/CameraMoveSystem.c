//! Called in ecs updates
void CameraMoveSystem(ecs_iter_t *it)
{
    double deltaTime = (double) (it->delta_time);
    double movementPower = 0.006 * 100 * deltaTime; // 2.8f; // * deltaTime;
    ecs_query_t *cameraQuery = it->ctx;
    if (!cameraQuery)
    {
        printf("[CameraMoveSystem; cameraQuery is void]\n");
        return;
    }
    ecs_iter_t cameraIter = ecs_query_iter(it->world, cameraQuery);
    ecs_query_next(&cameraIter);
    if (cameraIter.count == 0)
    {
        // printf("[404; Bob Not Found]\n");
        return;
    }
    // printf("Bobs Found [%i]\n", bobIter.count);
    Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    const CameraFree *cameraFrees = ecs_field(&cameraIter, CameraFree, 2);
    Position *positions = ecs_field(&cameraIter, Position, 3);
    const Rotation *rotations = ecs_field(&cameraIter, Rotation, 4);
    //Acceleration *accelerations = ecs_field(&bobIter, Acceleration, 2);
    //const Velocity *velocitys = ecs_field(&bobIter, Velocity, 3);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        float3 movement = { 0, 0, 0 };
        if (keyboard->a.isPressed)
        {
            movement.x = -1;
        }
        if (keyboard->d.isPressed)
        {
            movement.x = 1;
        }
        if (keyboard->w.isPressed)
        {
            movement.z = -1;
        }
        if (keyboard->s.isPressed)
        {
            movement.z = 1;
        }
        if (keyboard->q.isPressed)
        {
            movement.y = -1;
        }
        if (keyboard->e.isPressed)
        {
            movement.y = 1;
        }
        if (!(movement.x == 0 && movement.y == 0 && movement.z == 0))
        {
            // printf("Bob Accel %f x %f \n", movement.x, movement.y);
            movement.x *= movementPower;
            movement.y *= movementPower;
            movement.z *= movementPower;
            for (int j = 0; j < cameraIter.count; j++)
            {
                const CameraFree *cameraFree = &cameraFrees[j];
                if (cameraFree->value)
                {
                    const Rotation *rotation = &rotations[j];
                    float3 rotatedMovement = float4_rotate_float3(rotation->value, movement);
                    Position *position = &positions[j];
                    position->value.x += rotatedMovement.x;
                    position->value.y += rotatedMovement.y;
                    position->value.z += rotatedMovement.z;
                }
            }
        }
    }
}
ECS_SYSTEM_DECLARE(CameraMoveSystem);