// Define the FrameBufferLink component
zox_component(FrameBufferLink, uint)

// Destructor for FrameBufferLink component
ECS_DTOR(FrameBufferLink, ptr, {
    // zox_log(" - destroying frame buffer %i\n", ptr->value) // this should never really be called tho
    if (ptr->value) {
        glDeleteFramebuffers(1, &ptr->value);
    }
    ptr->value = 0;
})

// Function to generate a frame buffer object on gpu
uint gpu_spawn_frame_buffer_object() {
    uint buffer;
    glGenFramebuffers(1, &buffer);
#ifdef zoxel_catch_opengl_errors
    if (check_opengl_error_unlogged()) zox_log(" ! [gpu_spawn_frame_buffer_object] error at glGenFramebuffers\n")
#endif
    return buffer;
}

// Function to add a frame buffer object to a prefab
void prefab_add_frame_buffer_object(ecs_world_t *world, const ecs_entity_t e) {
    if (!headless) {
        zox_prefab_set(e, FrameBufferLink, { 0 })
    }
}

// Function to spawn and attach a frame buffer object to an entity
uint spawn_frame_buffer_object(ecs_world_t *world, const ecs_entity_t e) {
    if (headless) {
        return 0;
    }
    uint buffer = gpu_spawn_frame_buffer_object();
    zox_set(e, FrameBufferLink, { buffer })
    // zox_log(" + spawn_frame_buffer_object [%u]\n", buffer)
    return buffer;
}

// Attach the texture to the FBO
void connect_render_texture_to_fbo(const uint fbo, const uint texture) {
    // zox_log(" + connecting texture [%i] to fbo [%i]\n", texture, fbo)
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
#ifdef zoxel_catch_opengl_errors
    if (check_opengl_error_unlogged()) zox_log(" > failed fbo to texture [%i] : [%i]\n", fbo, texture)
#endif
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void set_render_texture_gpu(uint index, const int2 size) {
    // make it a render texture update system
    glBindTexture(GL_TEXTURE_2D, index);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
}
