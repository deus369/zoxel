const double movement_multiplier = 0.006 * 100;

//! Called in ecs updates
void FreeCameraMoveSystem(ecs_iter_t *it)
{
    ecs_iter_t cameras_it = ecs_query_iter(it->world, it->ctx);
    ecs_query_next(&cameras_it);
    if (cameras_it.count == 0)
    {
        return;
    }
    const FreeRoam *freeRoams = ecs_field(&cameras_it, FreeRoam, 2);
    Position *positions = ecs_field(&cameras_it, Position, 3);
    Rotation *rotations = ecs_field(&cameras_it, Rotation, 4);
    double movement_power = (double) (it->delta_time) * movement_multiplier;
    Keyboard *keyboards = ecs_field(it, Keyboard, 1);
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
            movement = float3_multiply_float(movement, movement_power);
            for (int j = 0; j < cameras_it.count; j++)
            {
                const FreeRoam *freeRoam = &freeRoams[j];
                if (freeRoam->value == 1)
                {
                    const Rotation *rotation = &rotations[j];
                    //printf("Before Movement: %fx%fx%f - [%fx%fx%fx%f]\n", movement.x, movement.y, movement.z,
                    //    rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
                    float3 rotatedMovement = float4_rotate_float3(rotation->value, movement);
                    Position *position = &positions[j];
                    position->value = float3_add(position->value, rotatedMovement);
                    // float4_print_euler(rotation->value);
                    // float3 rotatedMovement2 = float3_multiply_float(rotatedMovement, 10000);
                    // printf("Moving [%i x %i x %i]\n", (int) rotatedMovement2.x, (int) rotatedMovement2.y, (int) rotatedMovement2.z);
                    // printf("    Rotation [%f x %f x %f x %f]\n", rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
                }
            }
        }
        if (keyboard->r.wasPressedThisFrame)
        {
            for (int j = 0; j < cameras_it.count; j++)
            {
                Rotation *rotation = &rotations[j];
                rotation->value = quaternion_from_euler( (float3) { 0 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
            }
        }
    }
}
ECS_SYSTEM_DECLARE(FreeCameraMoveSystem);

        /*if (keyboard->x.wasPressedThisFrame)
        {
            for (int j = 0; j < cameraIter.count; j++)
            {
                Rotation *rotation = &rotations[j];
                rotation->value = quaternion_from_euler( (float3) { 0 * degreesToRadians, 90 * degreesToRadians, 0 * degreesToRadians });
            }
        }*/
        /*if (keyboard->v.wasPressedThisFrame)
        {
            for (int j = 0; j < cameraIter.count; j++)
            {
                Rotation *rotation = &rotations[j];
                rotation->value = quaternion_from_euler( (float3) { 0 * degreesToRadians, -90 * degreesToRadians, 0 * degreesToRadians });
            }
        }
        if (keyboard->b.wasPressedThisFrame)
        {
            printf("Rotating Upwards");
            for (int j = 0; j < cameraIter.count; j++)
            {
                Rotation *rotation = &rotations[j];
                rotation->value = quaternion_from_euler( (float3) { -90 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
            }
        }
        if (keyboard->n.wasPressedThisFrame)
        {
            printf("Rotating Downwards");
            for (int j = 0; j < cameraIter.count; j++)
            {
                Rotation *rotation = &rotations[j];
                rotation->value = quaternion_from_euler( (float3) { 90 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
            }
        }*/