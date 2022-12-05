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