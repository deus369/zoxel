// checks opengl for errors
int check_opengl_error(char* function_name) {
    int is_error = 0;
    GLenum error_code = glGetError();
    while (error_code != GL_NO_ERROR) {
        is_error = 1;
        // printf("check_opengl_error [%s] [%i]\n", function_name, (int) error_code);
        const char* error_message;
        switch (error_code) {
            case GL_INVALID_ENUM:
                error_message = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error_message = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error_message = "GL_INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error_message = "GL_STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error_message = "GL_STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error_message = "GL_OUT_OF_MEMORY";
                break;
            // new
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_message = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_TABLE_TOO_LARGE:
                error_message = "GL_TABLE_TOO_LARGE";
                break;
            case GL_INVALID_INDEX:
                error_message = "GL_INVALID_INDEX";
                break;
            // case GL_CONTEXT_LOST:
            //    error_message = "GL_CONTEXT_LOST";
            //    break;
            default:
                error_message = "UNKNOWN";
                break;
        }
        zoxel_log(" ! render error [%s]:[%d] - %s\n", error_message, error_code, function_name);
        error_code = glGetError();
    }
    return is_error;
}

byte check_opengl_error_unlogged() {
    byte is_error = 0;
    GLenum error_code = glGetError();
    while (error_code != GL_NO_ERROR) {
        is_error = 1;
        error_code = glGetError();
    }
    return is_error;
}

byte check_opengl_frame_buffer_status() {
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status == GL_FRAMEBUFFER_COMPLETE) return 1;
    char* error_code = "";
    switch (status) {
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            error_code = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
            // One or more framebuffer attachments are incomplete or not attached.
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            error_code = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
            // No images are attached to the framebuffer.
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            error_code = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
            // The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for one or more color attachments.
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            error_code = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
            // GL_READ_BUFFER is set to a buffer that does not have an image attached.
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            error_code = "GL_FRAMEBUFFER_UNSUPPORTED";
            // The combination of internal formats of the attached images violates an implementation-dependent set of restrictions.
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            error_code = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
            // The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; or the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES.
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            error_code = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
            // Not all attached images have the same width and height.
            break;
        default:
            error_code = "UKNOWN";
            // An unknown error occurred.
            break;
    }
    zox_log(" ! frame buffer incomplete [%s]\n", error_code)
    return 0;
}
