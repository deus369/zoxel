void camera_render_update(ecs_iter_t *it, const unsigned char is_camera2D) {
    unsigned char do_renders = !headless && rendering; // && !is_using_vulkan;
    if (!do_renders) return;
    opengl_set_defaults(!is_camera2D);
    zox_iter_world()
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
        GLuint fbo = 0;
        GLuint rbo = 0;
        if (!is_camera2D) {
            if (zox_has(e, FrameBufferLink)) {
                fbo = zox_get_value(e, FrameBufferLink)
            }
            if (zox_has(e, RenderBufferLink)) {
                rbo = zox_get_value(e, RenderBufferLink)
            }
        }
        if (!is_using_vulkan) {
            glViewport(screenPosition->value.x, screenPosition->value.y, screenDimensions->value.x, screenDimensions->value.y);
        }
        // todo: this required but breaks it for both render cameras
        // if (fbod) opengl_clear_viewport_depth();
        if (fbo) {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            if (!check_opengl_frame_buffer_status()) {
                zox_log(" !! camera render - error on fbo [%u]\n", fbo)
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                continue;
            }
            glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            if (check_opengl_error("glBindRenderbuffer")) {
                zoxel_log(" > glBindRenderbuffer GL_RENDERBUFFER %i [%i %i]\n", i, fbo, rbo);
            }
            GLfloat colorClearValue[4] = { 0.3f, 0.1f, 0.1f, 1.0f}; // RGBA
            GLfloat depthClearValue = 1.0f; // Usually 1.0f for depth.
            glClearBufferfv(GL_COLOR, 0, colorClearValue);
            if (check_opengl_error("glClearBufferfv GL_COLOR")) {
                zoxel_log(" > glClearBufferfv GL_COLOR %i [%i %i]\n", i, fbo, rbo);
            }
            glClearBufferfv(GL_DEPTH, 0, &depthClearValue);
            if (check_opengl_error("glClearBufferfv GL_DEPTH")) {
                zoxel_log(" > glClearBufferfv GL_DEPTH %i [%i %i]\n", i, fbo, rbo);
            }
        }
#ifdef zox_include_vulkan
        // else { set vulkan viewport; }
#endif
        if (!is_camera2D) {
            for (int j = 0; j < render3D_systems->size; j++) {
                ecs_run(world, render3D_systems->data[j], 0, NULL);
            }
        } else {
            for (renderer_layer = 0; renderer_layer < max_layers2D; renderer_layer++) { // ui rendered in layers
                for (int j = 0; j < render2D_systems->size; j++) {
                    ecs_run(world, render2D_systems->data[j], 0, NULL);
                }
            }
        }
        if (rbo) glBindRenderbuffer(GL_RENDERBUFFER, 0);
        if (fbo) glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

void CameraRender3DSystem(ecs_iter_t *it) {
    camera_render_update(it, 0);
} zox_declare_system(CameraRender3DSystem)

void CameraRenderUISystem(ecs_iter_t *it) {
    camera_render_update(it, 1);
} zox_declare_system(CameraRenderUISystem)

/*GLfloat depthClearValue = 1.0f; // Adjust as needed
glClearBufferSubData(GL_RENDERBUFFER, GL_DEPTH, 0, 0, GL_DEPTH_COMPONENT, GL_FLOAT, &depthClearValue);*/

/*void clear_viewport( unsigned char is_3D) {
    if (is_using_vulkan) {
#ifdef zox_include_vulkan
        vulkan_clear_viewport(viewport_clear_color);
#endif
    } else {
        opengl_clear_viewport(viewport_clear_color, is_3D);
    }
}*/
