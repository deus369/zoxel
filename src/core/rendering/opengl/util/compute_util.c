#include <string.h>

// uses opengl version to check iif compute is supported
int check_compute_shader_support_from_version() {
    const char* version_str = (const char*) glGetString(GL_VERSION);
    int is_opengl_es = strstr(version_str, "ES") != NULL;
    int major = 0, minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    if (is_opengl_es) {
        if (major >= 3 && minor >= 1) {
            #ifdef zoxel_debug_opengl
                zoxel_log(" > compute supported: OpenGL ES %d.%d [%s]\n", major, minor, version_str);
            #endif
            return EXIT_SUCCESS;
        }
    } else {
        if (major >= 4 && minor >= 3) {
            #ifdef zoxel_debug_opengl
                zoxel_log(" > compute supported: OpenGL %d.%d [%s]\n", major, minor, version_str);
            #endif
            return EXIT_SUCCESS;
        }
    }
    #ifdef zoxel_debug_opengl
        zoxel_log(" - compute not supported: OpenGL %d.%d [%s]\n", major, minor, version_str);
    #endif
    return EXIT_FAILURE;
}

// debugs compute shader support
int check_compute_shader_support() {
    check_opengl_error("[pre check_compute_shader_support Error]");
    // Check whether compute shaders are supported
    if (!glUseProgram) {
        zoxel_log(" - [glUseProgram] is not supported.\n");
        return EXIT_FAILURE;
    }
    if (!glDispatchCompute) {
        zoxel_log(" - [glDispatchCompute] is not supported.\n");
        return EXIT_FAILURE;
    }
    if (check_compute_shader_support_from_version() == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    #ifdef zoxel_debug_opengl
        zoxel_log("    > opengl compute stats\n");
    #endif
    // Get the maximum number of compute work groups
    GLint max_compute_group_count[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &max_compute_group_count[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &max_compute_group_count[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &max_compute_group_count[2]);
    #ifdef zoxel_debug_opengl
        zoxel_log("        + count [%d, %d, %d]\n", max_compute_group_count[0], max_compute_group_count[1], max_compute_group_count[2]);
    #endif
    int is_error = check_opengl_error("[GL_MAX_COMPUTE_WORK_GROUP_COUNT Error]");
    if (is_error) {
        #ifdef zoxel_debug_opengl
            zoxel_log(" - GL_MAX_COMPUTE_WORK_GROUP_COUNT is not supported\n");
        #endif
        return EXIT_FAILURE;
    }
    // Get the maximum compute work group size
    GLint max_compute_group_size[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &max_compute_group_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &max_compute_group_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &max_compute_group_size[2]);
    #ifdef zoxel_debug_opengl
        zoxel_log("        + size [%d, %d, %d]\n", max_compute_group_size[0], max_compute_group_size[1], max_compute_group_size[2]);
    #endif
    is_error = check_opengl_error("[GL_MAX_COMPUTE_WORK_GROUP_SIZE Error]");
    if (is_error) {
        #ifdef zoxel_debug_opengl
            zoxel_log(" - GL_MAX_COMPUTE_WORK_GROUP_SIZE is not supported\n");
        #endif
        return EXIT_FAILURE;
    }
    // Get the maximum compute work group invocations
    GLint max_compute_work_group_invocations;
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &max_compute_work_group_invocations);
    #ifdef zoxel_debug_opengl
        zoxel_log("        + invocations [%d]\n", max_compute_work_group_invocations);
    #endif
    is_error = check_opengl_error("[GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS Error]");
    if (is_error) {
        #ifdef zoxel_debug_opengl
            zoxel_log(" - GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS is not supported\n");
        #endif
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int test_compute_shader() {
    uint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    if (compute_shader == 0) {
        zoxel_log("    - compute shader creation failed\n");
        return EXIT_FAILURE;
    } else {
        zoxel_log("    > compute shader creation success\n");
        glDeleteShader(compute_shader);
        return EXIT_SUCCESS;
    }
}