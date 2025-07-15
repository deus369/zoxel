zox_component(RenderBufferLink, uint)

// Destructor for RenderBufferLink component
ECS_DTOR(RenderBufferLink, ptr, {
    if (ptr->value) glDeleteRenderbuffers(1, &ptr->value);
    ptr->value = 0;
})

void set_render_buffer_size(const uint rbo, const int2 dimensions) {
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    // GL_DEPTH24_STENCIL8 GL_DEPTH
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, dimensions.x, dimensions.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // Check for OpenGL errors
#ifdef zoxel_catch_opengl_errors
    if (check_opengl_error("glRenderbufferStorage")) {
        zox_log("     > glRenderbufferStorage [%i]\n", rbo)
    }
#endif
}

// Create and attach a renderbuffer for depth and stencil (optional, depending on needs)
uint gpu_spawn_render_buffer(const int2 dimensions) {
    uint rbo;
    glGenRenderbuffers(1, &rbo);
    // Check for OpenGL errors
#ifdef zoxel_catch_opengl_errors
    if (check_opengl_error("glGenRenderbuffers")) {
        // zox_log("     > glGenRenderbuffers\n")
        return 0; // Return 0 or some other error value
    }
#endif
    set_render_buffer_size(rbo, dimensions);
    return rbo;
}

void prefab_add_render_buffer(ecs_world_t *world, const ecs_entity_t e) {
    if (!headless) zox_prefab_set(e, RenderBufferLink, { 0 })
}

uint spawn_render_buffer(ecs_world_t *world, const ecs_entity_t e, const int2 dimensions) {
    if (headless) return 0;
    uint buffer = gpu_spawn_render_buffer(dimensions);
    zox_set(e, RenderBufferLink, { buffer })
    // zox_log(" + spawn_render_buffer [%u]\n", buffer)
    return buffer;
}

void connect_render_buffer_to_fbo(const uint fbo, const uint render_buffer) {
    // zox_log(" + connecting fbo [%u] to render_buffer [%u]\n", fbo, render_buffer)
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_buffer);
    if (!check_opengl_frame_buffer_status()) {
        zox_log(" !!! connect_render_buffer_to_fbo error on fbo [%u]\n", fbo)
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return;
    }
#ifdef zoxel_catch_opengl_errors
    if (check_opengl_error_unlogged()) zox_log(" > failed fbo to render_buffer [%i] : [%i]\n", fbo, render_buffer)
#endif
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
