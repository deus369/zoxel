//! Use this until i can support multiple cameras
//! Spawn a Camera
/**
 * Give the camera a Transform, a ViewMatrix.
 * Animate it moving a little upwards.
*/

void resize_camera(ecs_world_t *world, ecs_entity_t e, int2 new_screen_dimensions)
{
    if (e && ecs_is_alive(world, e))
    {
        ecs_set(world, e, ScreenDimensions, { new_screen_dimensions });
    }
}

//! Uses ecs_get_mut to resize cameras. \todo Create a viewport resize event.
void resize_cameras(int width, int height)
{
    int2 new_screen_dimensions = (int2) { width, height };
    for (int i = 0; i < main_cameras_count; i++)
    {
        resize_camera(world, main_cameras[i], new_screen_dimensions);
    }
    resize_camera(world, ui_cameras[0], new_screen_dimensions);
}

/*ScreenDimensions *screenDimensions = ecs_get_mut(world, e, ScreenDimensions);
screenDimensions->value.x = width;
screenDimensions->value.y = height;
ecs_modified(world, e, ScreenDimensions);*/

/*ecs_entity_t e = cameras[i];
if (e && ecs_is_alive(world, e))
{
    ScreenDimensions *screenDimensions = ecs_get_mut(world, e, ScreenDimensions);
    screenDimensions->value.x = width;
    screenDimensions->value.y = height;
    ecs_modified(world, e, ScreenDimensions);
}*/

/*const float4x4 GetMainCameraViewMatrix()
{
    ecs_entity_t main_camera = get_main_camera();
    if (!main_camera || !ecs_is_alive(world, main_camera))
    {
        return float4x4_zero();
    }
    const ViewMatrix *viewMatrix = ecs_get(world, main_camera, ViewMatrix);
    return viewMatrix->value;
}*/

/*ecs_entity_t get_main_camera2()
{
    return main_cameras[1];
}

void set_main_camera2(ecs_entity_t camera)
{
    main_cameras[1] = camera;
}*/

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

/*void set_main_camera(ecs_entity_t camera)
{
    cameras[0] = camera;
}*/

/*ecs_entity_t get_main_camera()
{
    return cameras[0];
}*/