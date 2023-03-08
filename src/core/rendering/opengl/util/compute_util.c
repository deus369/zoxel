// debugs compute shader support
int check_compute_shader_support()
{
    // Check whether compute shaders are supported
    if (!glUseProgram)
    {
        printf("glUseProgram is not supported\n");
        return 0;
    }
    if (!glDispatchCompute)
    {
        printf("glDispatchCompute is not supported\n");
        return 0;
    }
    printf("    Compute Work Group Data\n");
    // Get the maximum number of compute work groups
    GLint max_compute_group_count[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &max_compute_group_count[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &max_compute_group_count[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &max_compute_group_count[2]);
    printf("        - count [%d, %d, %d]\n",
        max_compute_group_count[0], max_compute_group_count[1], max_compute_group_count[2]);
    int is_error = check_opengl_error("[GL_MAX_COMPUTE_WORK_GROUP_COUNT Error]");
    if (is_error)
    {
        printf("GL_MAX_COMPUTE_WORK_GROUP_COUNT is not supported\n");
        return 0;
    }
    // Get the maximum compute work group size
    GLint max_compute_group_size[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &max_compute_group_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &max_compute_group_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &max_compute_group_size[2]);
    printf("        - size [%d, %d, %d]\n",
        max_compute_group_size[0], max_compute_group_size[1], max_compute_group_size[2]);
    is_error = check_opengl_error("[GL_MAX_COMPUTE_WORK_GROUP_SIZE Error]");
    if (is_error)
    {
        printf("GL_MAX_COMPUTE_WORK_GROUP_SIZE is not supported\n");
        return 0;
    }
    // Get the maximum compute work group invocations
    GLint max_compute_work_group_invocations;
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &max_compute_work_group_invocations);
    printf("        - invocations [%d]\n", max_compute_work_group_invocations);
    is_error = check_opengl_error("[GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS Error]");
    if (is_error)
    {
        printf("GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS is not supported\n");
        return 0;
    }
    return 1;
}

int test_compute_shader() {
    GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    if (compute_shader == 0) {
        printf("Error creating compute shader.\n");
        return 1;
    } else {
        printf("Compute shader works.\n");
        glDeleteShader(compute_shader);
        return 0;
    }
}