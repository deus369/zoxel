// restore render buffer for camera
void RenderBufferRestoreSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(ScreenDimensions)
    zox_sys_out(FrameBufferLink)
    zox_sys_out(RenderBufferLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ScreenDimensions, screenDimensions)
        zox_sys_o(FrameBufferLink, frameBufferLink)
        zox_sys_o(RenderBufferLink, renderBufferLink)
        frameBufferLink->value = gpu_spawn_frame_buffer_object();
        renderBufferLink->value = gpu_spawn_render_buffer(screenDimensions->value);
        if (frameBufferLink->value && renderBufferLink->value) {
            connect_render_buffer_to_fbo(frameBufferLink->value, renderBufferLink->value);
        }
    }
} zox_declare_system(RenderBufferRestoreSystem)