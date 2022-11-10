//! Use this until i can support multiple cameras
//! Spawn a Camera
/**
 * Give the camera a Transform, a ViewMatrix.
 * Animate it moving a little upwards.
*/

ecs_entity_t get_main_camera()
{
    return cameras[0];
}

//! Uses ecs_get_mut to resize cameras. \todo Create a viewport resize event.
void resize_cameras(int width, int height)
{
    for (int i = 0; i < 2; i++)
    {
        ecs_entity_t e = cameras[i];
        if (e && ecs_is_alive(world, e))
        {
            ScreenDimensions *screenDimensions = ecs_get_mut(world, e, ScreenDimensions);
            screenDimensions->value.x = width;
            screenDimensions->value.y = height;
            ecs_modified(world, e, ScreenDimensions);
        }
    }
}

const float4x4 GetMainCameraViewMatrix()
{
    ecs_entity_t main_camera = get_main_camera();
    if (!main_camera || !ecs_is_alive(world, main_camera))
    {
        return float4x4_zero();
    }
    const ViewMatrix *viewMatrix = ecs_get(world, main_camera, ViewMatrix);
    return viewMatrix->value;
}

ecs_entity_t spawn_main_camera(ecs_world_t *world, int2 screenDimensions)
{
    cameras[0] = spawn_camera(world, (float3) { 0, -0.0f, 0.62f }, quaternion_identity(), screenDimensions);
    return cameras[0];
}

//! Used for testing cleanup
// void DestroyMainCamera()
// {
//     ecs_delete(world, mainCamera);
// }

// float3 spawnPosition = ;
// imagine this is a forward rotation
// float4 flipRotation = quaternion_from_euler( (float3) { 0, 180 * degreesToRadians, 0 });
// float4 flipRotation = quaternion_from_euler( (float3) { 0, 0 * degreesToRadians, 0 });
// ; // quaternion_from_euler( (float3) { 0 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
// spawnRotation = quaternion_rotate(flipRotation, spawnRotation);