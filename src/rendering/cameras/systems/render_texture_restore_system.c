void RenderTextureRestoreSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(TextureGPULink, textureGPULinks, 1)
    zox_field_in(PixelSize, screenDimensionss, 2)
    zox_field_in(CameraLink, cameraLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        zox_field_i(PixelSize, screenDimensionss, screenDimensions)
        zox_field_i(CameraLink, cameraLinks, cameraLink)
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