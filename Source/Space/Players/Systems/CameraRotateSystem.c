//! Called in ecs updates
void CameraRotateSystem(ecs_iter_t *it)
{
    // while right click only, and hide mouse!
    double deltaTime = (double) (it->delta_time);
    float rotatePower = 0.92f * 100 * deltaTime * degreesToRadians;
#ifdef __EMSCRIPTEN__
    rotatePower /= 8.0f;
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
    Euler *eulers = ecs_field(&cameraIter, Euler, 4);
    for (int i = 0; i < it->count; i++)
    {
        const Mouse *mouse = &mouses[i];
        float3 eulerAddition = { 0, -mouse->delta.x, -mouse->delta.y };
        eulerAddition = float3_multiply_float(eulerAddition, rotatePower);
        if (mouse->right.wasPressedThisFrame || !(eulerAddition.x == 0 && eulerAddition.y == 0 && eulerAddition.z == 0))
        {
            for (int j = 0; j < cameraIter.count; j++)
            {
                CameraFree *cameraFree = &cameraFrees[j];
                if (mouse->right.wasPressedThisFrame)
                {
                    cameraFree->value = !cameraFree->value;
                    printf("Camera Free Toggled [%s]\n", cameraFree->value ? "true" : "false");
                }
                if (mouse->left.isPressed || cameraFree->value)
                {
                    Euler *euler = &eulers[j];
                    euler->value = float3_add_float3(euler->value, eulerAddition);
                    Rotation *rotation = &rotations[j];
                    // rotation->value = quaternion_rotate(quaternion_from_euler(eulerAddition), rotation->value);
                    rotation->value = quaternion_from_euler(euler->value);
                    // float3_print(euler->value);
                }
            }
        }
    }
}
ECS_SYSTEM_DECLARE(CameraRotateSystem);


// rotate = float3_multiply_float(rotate, rotatePower);
// rotateQuaternion = float4_multiply_float(rotateQuaternion, rotatePower);
/*float4 rotateY = quaternion_from_euler((float3) { 0, -mouse->delta.x * rotatePower, 0 });
float4 rotateZ = quaternion_from_euler((float3) { 0, 0, -mouse->delta.y * rotatePower });
float4 rotateQuaternion = { 0, 0, 0, 1 };
rotateQuaternion = quaternion_rotate(rotateQuaternion, rotateY);
rotateQuaternion = quaternion_rotate(rotateQuaternion, rotateZ);*/