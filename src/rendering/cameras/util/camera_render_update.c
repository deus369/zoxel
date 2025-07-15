void camera_render_update(ecs_iter_t *it, const byte is_camera2D) {
    byte do_renders = !headless && rendering;
    if (!do_renders) {
        return;
    }
    opengl_set_defaults(!is_camera2D);
    zox_field_world()
    zox_field_in(ViewMatrix, viewMatrixs, 1)
    zox_field_in(FieldOfView, fieldOfViews, 2)
    zox_field_in(ScreenPosition, screenPositions, 3)
    zox_field_in(ScreenDimensions, screenDimensionss, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(ScreenPosition, screenPositions, screenPosition)
        zox_field_i(ScreenDimensions, screenDimensionss, screenDimensions)
        zox_field_i(ViewMatrix, viewMatrixs, viewMatrix)
        zox_field_i(FieldOfView, fieldOfViews, fieldOfView)
        // pass these data to systems
        renderer_camera = e;
        render_camera_fov = fieldOfView->value;
        render_camera_matrix = viewMatrix->value;
        // set render objects
        uint fbo = 0;
        if (!is_camera2D) {
            if (zox_has(e, FrameBufferLink)) fbo = zox_get_value(e, FrameBufferLink)
        }
        if (render_backend == zox_render_backend_opengl) {
            if (fbo) {
                glViewport(0, 0, screenDimensions->value.x, screenDimensions->value.y);
            } else {
                glViewport(screenPosition->value.x, screenPosition->value.y, screenDimensions->value.x, screenDimensions->value.y);
            }
        }
        // todo: this required but breaks it for both render cameras
        if (fbo) {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
#ifdef zoxel_catch_opengl_errors
            if (!check_opengl_frame_buffer_status()) {
                zox_log(" !! camera render - error on fbo [%u]\n", fbo)
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                continue;
            }
#endif
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
#ifdef zox_include_vulkan
        // else { set vulkan viewport; }
#endif
        if (!is_camera2D) {
            for (int j = 0; j < render3D_systems->size; j++) {
                ecs_run(world, render3D_systems->data[j], 0, NULL);
            }
            for (int j = 0; j < render3D_plus_systems->size; j++) {
                ecs_run(world, render3D_plus_systems->data[j], 0, NULL);
            }
        } else {
            for (renderer_layer = 0; renderer_layer < max_layers2D; renderer_layer++) { // ui rendered in layers
                for (int j = 0; j < render2D_systems->size; j++) {
                    ecs_run(world, render2D_systems->data[j], 0, NULL);
                }
            }
        }
        if (fbo) {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }
}