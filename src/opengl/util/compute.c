// uses opengl version to check iif compute is supported
int check_compute_shader_support_from_version() {
    const char* version_str = (const char*) glGetString(GL_VERSION);
    if (!version_str) {
        zox_log_error("GL not enabled.");
        return EXIT_FAILURE;
    }
    int is_opengl_es = strstr(version_str, "ES") != NULL;
    int major = 0, minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    if (is_opengl_es) {
        if (major >= 3 && minor >= 1) {
            zox_log_sdl("+ compute supported: OpenGL ES %d.%d [%s]", major, minor, version_str)
            return EXIT_SUCCESS;
        }
    } else {
        if (major >= 4 && minor >= 3) {
            zox_log_sdl("+ compute supported: OpenGL %d.%d [%s]", major, minor, version_str)
            return EXIT_SUCCESS;
        }
    }
    if (is_log_sdl) {
        zox_log_error("compute not supported: OpenGL %d.%d [%s]", major, minor, version_str)
    }
    return EXIT_FAILURE;
}

// debugs compute shader support
int check_compute_shader_support() {
    check_opengl_error("[pre check_compute_shader_support Error]");
    if (check_compute_shader_support_from_version() == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
#ifdef zoxel_debug_opengl
    zox_log("    > opengl compute stats\n")
#endif
    // Get the maximum number of compute work groups
    /*GLint max_compute_group_count[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &max_compute_group_count[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &max_compute_group_count[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &max_compute_group_count[2]);
    #ifdef zoxel_debug_opengl
        zox_log("        + count [%d, %d, %d]\n", max_compute_group_count[0], max_compute_group_count[1], max_compute_group_count[2]);
    #endif
    int is_error = check_opengl_error("[GL_MAX_COMPUTE_WORK_GROUP_COUNT Error]");
    if (is_error) {
        #ifdef zoxel_debug_opengl
            zox_log(" - GL_MAX_COMPUTE_WORK_GROUP_COUNT is not supported\n");
        #endif
        return EXIT_FAILURE;
    }
    // Get the maximum compute work group size
    GLint max_compute_group_size[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &max_compute_group_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &max_compute_group_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &max_compute_group_size[2]);
    #ifdef zoxel_debug_opengl
        zox_log("        + size [%d, %d, %d]\n", max_compute_group_size[0], max_compute_group_size[1], max_compute_group_size[2]);
    #endif
    is_error = check_opengl_error("[GL_MAX_COMPUTE_WORK_GROUP_SIZE Error]");
    if (is_error) {
        #ifdef zoxel_debug_opengl
            zox_log(" - GL_MAX_COMPUTE_WORK_GROUP_SIZE is not supported\n");
        #endif
        return EXIT_FAILURE;
    }
    // Get the maximum compute work group invocations
    GLint max_compute_work_group_invocations;
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &max_compute_work_group_invocations);
    #ifdef zoxel_debug_opengl
        zox_log("        + invocations [%d]\n", max_compute_work_group_invocations);
    #endif
    is_error = check_opengl_error("[GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS Error]");
    if (is_error) {
        #ifdef zoxel_debug_opengl
            zox_log(" - GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS is not supported\n");
        #endif
        return EXIT_FAILURE;
    }*/
    return EXIT_SUCCESS;
}

// removed compute test for now, broke on android version
void check_compute() {
    if (check_compute_shader_support() == EXIT_FAILURE) {
        zox_log_error("opengl compute is not supported")
    } else {
        zox_log_sdl("+ opengl compute supported")
    }
}

int test_compute_shader() {
    uint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    if (compute_shader == 0) {
        zox_log("    - compute shader creation failed\n");
        return EXIT_FAILURE;
    } else {
        zox_log("    > compute shader creation success\n");
        glDeleteShader(compute_shader);
        return EXIT_SUCCESS;
    }
}