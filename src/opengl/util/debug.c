// Print All Supported Extensions
void print_opengl_functions() {
    GLint numExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    zox_log("+ OpenGL Extensions: %d", numExtensions);
    const GLubyte *extensions = glGetString(GL_EXTENSIONS);
    if (!extensions) {
        zox_log_error("Could not retrieve extensions [%s]", SDL_GetError())
    } else {
        // zox_log(" - gl extensions: %s", extensions);
        /*for (int i = 0; i < numExtensions; ++i) {
            zox_log("%s\n", glGetStringi(GL_EXTENSIONS, i))
        }*/
    }
}

void print_opengl() {
    zox_log(" > OpenGL")
    zox_log("     + version   [%s]", glGetString(GL_VERSION))
    zox_log("     + glsl      [%s]", glGetString(GL_SHADING_LANGUAGE_VERSION))
    zox_log("     + vendor    [%s]", glGetString(GL_VENDOR))
    zox_log("     + renderer  [%s]", glGetString(GL_RENDERER))
    /*GLint memory_used, memory_total;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
    glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
    zox_log("     + GPU Memory Usage [%d MB / %d MB]\n", memory_used / 1024, memory_total / 1024);
    check_opengl_error("[print_opengl Error]");*/
    print_opengl_functions();
}