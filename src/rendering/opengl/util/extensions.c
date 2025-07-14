byte has_gl_extension(const GLubyte *extensions, const char *target) {
    if (extensions == NULL || target == NULL) {
        return 0;
    }
    const char *token = strtok((char *) extensions, " ");
    while (token != NULL) {
        if (strcmp(token, target) == 0) {
            return 1; // Extension found
        }
        token = strtok(NULL, " ");
    }
    return 0; // Extension not found
}

byte has_opengl_extensions() {
    byte has_extension = 1;
    const GLubyte *extensions = glGetString(GL_EXTENSIONS);
    /*if (extensions != NULL) printf("        > gl extensions: %s\n", extensions);
    else fprintf(stderr, "Error retrieving extensions\n");*/
#if !defined(zoxel_on_web) && !defined(zoxel_on_android)
    if (!has_gl_extension(extensions, "GL_ARB_shader_objects")) {
        zox_log_error("Extension not found [GL_ARB_shader_objects]")
        has_extension = 0;
    }
#endif
    return has_extension;
}