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
            default:
                error_message = "UNKNOWN";
                break;
        }
        zoxel_log(" ! render error [%s]:[%d] - %s\n", error_message, error_code, function_name);
        error_code = glGetError();
    }
    return is_error;
}

unsigned char check_opengl_error_unlogged() {
    unsigned char is_error = 0;
    GLenum error_code = glGetError();
    while (error_code != GL_NO_ERROR) {
        is_error = 1;
        error_code = glGetError();
    }
    return is_error;
}