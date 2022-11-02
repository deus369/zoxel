//! Called in ecs updates
void CameraRotateSystem(ecs_iter_t *it)
{
    // while right click only, and hide mouse!
    double deltaTime = (double) (it->delta_time);
    float rotatePower = 0.08f * 100 * deltaTime;
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
        return;
    }
    Mouse *mouses = ecs_field(it, Mouse, 1);
    Rotation *rotations = ecs_field(&cameraIter, Rotation, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Mouse *mouse = &mouses[i];
        if (!mouse->right.isPressed)
        {
            return;
        }
        float3 rotate = { 0, mouse->delta.y, -mouse->delta.x };
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
            for (int j = 0; j < cameraIter.count; j++)
            {
                Rotation *rotation = &rotations[j];
                rotation->value = quaternion_rotate(rotate3, rotation->value);
            }
        }
    }
}
ECS_SYSTEM_DECLARE(CameraRotateSystem);