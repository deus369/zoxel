void create_camera_rbo_and_fbo(ecs_world_t *world,
    const ecs_entity_t e,
    const int2 size)
{
#ifndef zox_disable_post_processing
    uint fbo = spawn_frame_buffer_object(world, e);
    uint render_buffer = spawn_render_buffer(world, e, size);
    if (fbo && render_buffer) {
        connect_render_buffer_to_fbo(fbo, render_buffer);
    }
#endif
}