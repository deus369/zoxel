//! Called in ecs updates
void CameraRotateSystem(ecs_iter_t *it)
{
    // while right click only, and hide mouse!
    double deltaTime = (double) (it->delta_time);
    float rotatePower = 0.12f * 100 * deltaTime;
#ifdef __EMSCRIPTEN__
    rotatePower /= 3.0f;
#endif
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
    CameraFree *cameraFrees = ecs_field(&cameraIter, CameraFree, 3);
    for (int i = 0; i < it->count; i++)
    {
        const Mouse *mouse = &mouses[i];
        float3 rotate = { 0, -mouse->delta.x, -mouse->delta.y };
        // if (!(rotate.x == 0 && rotate.y == 0 && rotate.z == 0))
        {
            rotate = float3_multiply_float(rotate, rotatePower * degreesToRadians);
            float4 rotateQuaternion = quaternion_from_euler(rotate);
            // printf("rotate: %fx%f\n", rotate.x, rotate.y);
            for (int j = 0; j < cameraIter.count; j++)
            {
                CameraFree *cameraFree = &cameraFrees[j];
                if (mouse->left.wasPressedThisFrame)
                {
                    Rotation *rotation = &rotations[j];
                    rotation->value = quaternion_identity();
                    printf("Camera Rotation Reset.\n");
                    return;
                }
                if (mouse->middle.wasPressedThisFrame)
                {
                    cameraFree->value = !cameraFree->value;
                    printf("Camera Free Toggled [%s]\n", cameraFree->value ? "true" : "false");
                }
                if (mouse->right.isPressed || cameraFree->value)
                {
                    Rotation *rotation = &rotations[j];
                    rotation->value = quaternion_rotate(rotateQuaternion, rotation->value);
                }
            }
        }
    }
}
ECS_SYSTEM_DECLARE(CameraRotateSystem);