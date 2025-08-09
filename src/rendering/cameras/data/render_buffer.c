zoxc(RenderBufferLink, uint);

// Destructor for RenderBufferLink component
ECS_DTOR(RenderBufferLink, ptr, {
    if (ptr->value) {
        glDeleteRenderbuffers(1, &ptr->value);
    }
    ptr->value = 0;
})

// GL_DEPTH24_STENCIL8 GL_DEPTH
void set_render_buffer_size(const uint rbo, const int2 size) {
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH24_STENCIL8,
        size.x,
        size.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

// Create and attach a renderbuffer for depth and stencil (optional, depending on needs)
uint gpu_spawn_render_buffer(const int2 size) {
    uint rbo;
    glGenRenderbuffers(1, &rbo);
    set_render_buffer_size(rbo, size);
    return rbo;
}

void prefab_add_render_buffer(ecs *world, const entity e) {
    if (!headless) {
        zox_prefab_set(e, RenderBufferLink, { 0 })
    }
}

uint spawn_render_buffer(ecs *world, const entity e, const int2 size) {
    if (headless) {
        return 0;
    }
    uint buffer = gpu_spawn_render_buffer(size);
    zox_set(e, RenderBufferLink, { buffer })
    // zox_log(" + spawn_render_buffer [%u]\n", buffer)
    return buffer;
}

void connect_render_buffer_to_fbo(const uint fbo, const uint render_buffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_buffer);
    if (!check_opengl_frame_buffer_status()) {
        zox_log(" !!! connect_render_buffer_to_fbo error on fbo [%u]\n", fbo)
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
