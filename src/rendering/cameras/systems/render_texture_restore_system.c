void RenderTextureRestoreSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TextureGPULink)
    zox_sys_in(PixelSize)
    zox_sys_in(CameraLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TextureGPULink, textureGPULink)
        zox_sys_i(PixelSize, screenDimensions)
        zox_sys_i(CameraLink, cameraLink)
        set_render_texture_gpu(textureGPULink->value, screenDimensions->value);
        if (zox_has(cameraLink->value, FrameBufferLink)) {
            const uint fbo = zox_get_value(cameraLink->value, FrameBufferLink)
            connect_render_texture_to_fbo(fbo, textureGPULink->value);
            // zox_log("> reconnected texture link [%i] to fbo [%i]\n", textureGPULink->value, fbo)
        } else {
            zox_log("! camera does not have frame buffer link: %i\n", cameraLink->value)
        }
    }
} zox_declare_system(RenderTextureRestoreSystem)