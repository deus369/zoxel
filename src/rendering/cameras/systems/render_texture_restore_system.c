void RenderTextureRestoreSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TextureGPULink)
    zox_sys_in(TextureSize)
    zox_sys_in(CameraLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TextureGPULink, textureGPULink)
        zox_sys_i(TextureSize, textureSize)
        zox_sys_i(CameraLink, cameraLink)
        ecs_entity_t camera = cameraLink->value;
        if (zox_has(camera, FrameBufferLink)) {
            // Refresh Render Camera
            uint fbo = spawn_frame_buffer_object(world, camera);
            uint rbo = spawn_render_buffer(world, camera, textureSize->value);
            if (fbo && rbo) {
                connect_render_buffer_to_fbo(fbo, rbo);
            }
            // Refresh Texture
            set_render_texture_gpu(textureGPULink->value, textureSize->value);
            connect_render_texture_to_fbo(fbo, textureGPULink->value);
            set_render_buffer_size(rbo, textureSize->value);
            if (is_log_gpu_restore) {
                zox_sys_world()
                zox_sys_e()
                zox_log("+ restoring render_texture [%s]\n", zox_get_name(e))
                zox_log("   - texture [%i] linked to fbo [%i] and rbo [%i]", textureGPULink->value, fbo, rbo)
            }
        } else {
            zox_log_error("camera does not have frame buffer link: %lu", cameraLink->value)
        }
    }
} zox_declare_system(RenderTextureRestoreSystem)