//! Called in ecs updates
void FreeCameraRotateSystem(ecs_iter_t *it)
{
    // while right click only, and hide mouse!
    double deltaTime = (double) (it->delta_time);
    float rotatePower = 0.62f * deltaTime * degreesToRadians;
#ifdef WEB_BUILD
    rotatePower *= 16.0f;
#else
    rotatePower *= 32.0f;
#endif
    ecs_query_t *cameraQuery = it->ctx;
    if (!cameraQuery)
    {
        zoxel_log("[FreeCameraMoveSystem; cameraQuery is null]\n");
        return;
    }
    ecs_iter_t cameraIter = ecs_query_iter(it->world, cameraQuery);
    ecs_query_next(&cameraIter);
    if (cameraIter.count == 0)
    {
        return;
    }
    Mouse *mouses = ecs_field(it, Mouse, 1);
    const FreeRoam *freeRoams = ecs_field(&cameraIter, FreeRoam, 2);
    Euler *eulers = ecs_field(&cameraIter, Euler, 3);
    for (int i = 0; i < it->count; i++)
    {
        const Mouse *mouse = &mouses[i];
        float3 eulerAddition = { 0, -mouse->delta.x, mouse->delta.y };
        eulerAddition = float3_multiply_float(eulerAddition, rotatePower);
        if (!(eulerAddition.x == 0 && eulerAddition.y == 0 && eulerAddition.z == 0))
        {
            for (int j = 0; j < cameraIter.count; j++)
            {
                const FreeRoam *freeRoam = &freeRoams[j];
                Euler *euler = &eulers[j];
                if (freeRoam->value == 1)  // mouse->left.is_pressed || 
                {
                    // printf("mouse->delta: %ix%i\n", mouse->delta.x, mouse->delta.y);
                    euler->value = float3_add(euler->value, eulerAddition);
                    // Rotation3D *rotation = &rotations[j];
                    // rotation->value = quaternion_rotate(quaternion_from_euler(eulerAddition), rotation->value);
                    // rotation->value = quaternion_from_euler(euler->value);
                    // float3_print(euler->value);
                }
                /*else
                {
                    euler->value = (float3) { 0, 0, 0 };
                }*/
            }
        }
    }
}
zoxel_declare_system(FreeCameraRotateSystem)