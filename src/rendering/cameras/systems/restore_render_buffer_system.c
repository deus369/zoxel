// restore render buffer for camera
void RenderBufferRestoreSystem(ecs_iter_t *it) {
    zox_field_in(ScreenDimensions, screenDimensionss, 1)
    zox_field_out(FrameBufferLink, frameBufferLinks, 2)
    zox_field_out(RenderBufferLink, renderBufferLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ScreenDimensions, screenDimensionss, screenDimensions)
        zox_field_o(FrameBufferLink, frameBufferLinks, frameBufferLink)
        zox_field_o(RenderBufferLink, renderBufferLinks, renderBufferLink)
        frameBufferLink->value = gpu_spawn_frame_buffer_object();
        renderBufferLink->value = gpu_spawn_render_buffer(screenDimensions->value);
        if (frameBufferLink->value && renderBufferLink->value) {
            connect_render_buffer_to_fbo(frameBufferLink->value, renderBufferLink->value);
        }
    }
} zox_declare_system(RenderBufferRestoreSystem)