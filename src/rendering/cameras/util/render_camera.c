void initialize_camera_post_processing(ecs_world_t *world,
    const ecs_entity_t e,
    const int2 viewport_size)
{
#ifndef zox_disable_post_processing
    uint fbo = spawn_frame_buffer_object(world, e); // test fbo
    uint render_buffer = spawn_render_buffer(world, e, viewport_size); // test fbo
    if (fbo && render_buffer) {
        connect_render_buffer_to_fbo(fbo, render_buffer);
    }
#endif
}