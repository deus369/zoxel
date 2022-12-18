//! Closes the game when button is clicked.
void PlayGameButtonSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    // printf("WindowCloseSystem [%i]\n", it->count);
    const ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    for (int i = 0; i < it->count; i++)
    {
        const ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value == 1)
        {
            // destroy ui
            //! window is 2nd parent
            const ParentLink *parentLink = ecs_get(world, it->entities[i], ParentLink);
            // const ParentLink *parentParentLink = ecs_get(it->world, parentLink->value, ParentLink);
            ecs_entity_t window = parentLink->value;
            delete_hierarchy(world, window);
            // ecs_delete(it->world, window);
            // destroy ai camera
            ecs_entity_t first_camera = main_cameras[0];
            float3 first_camera_position = ecs_get(world, first_camera, Position)->value;
            float4 first_camera_rotation = ecs_get(world, first_camera, Rotation)->value;
            float4x4 first_view_matrix = ecs_get(world, first_camera, ViewMatrix)->value;
            int2 first_camera_screen_dimensions = ecs_get(world, first_camera, ScreenDimensions)->value;
            ecs_delete(world, first_camera);
            // spawn free roam camera
            // \todo I believe the flickering is due to the matrix not being set in time.
            main_cameras[0] = spawn_free_camera(world, first_camera_position, // (float3) { 0, 3.6f, 0.62f },
                first_camera_rotation, first_camera_screen_dimensions, (int2) { });
            ecs_set(world, main_cameras[0], ViewMatrix, { first_view_matrix });
            // \todo Fix issue with rotation, due to euler setting, make sure to set euler when spawning cameras
        }
    }
}
ECS_SYSTEM_DECLARE(PlayGameButtonSystem);