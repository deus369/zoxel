// cc -std=c99 tests/opengl/compute_simpler.c -o compute_simpler -lGL -lGLEW -lglfw && ./compute_simpler
#define zox_logs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../src/core/util/logs.c"
#include "../../src/core/rendering/opengl/util/error_util.c"
#include "../../src/core/rendering/opengl/util/compute_util.c"
#include "glfw_util.c"
#include "glew_util.c"

#define buffer_type GL_SHADER_STORAGE_BUFFER
const char* compute_shader_source = "\
#version 310 es\n\
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;\
buffer PositionBuffer {\
    int values[];\
};\
void main() {\
    int index = int(gl_WorkGroupID.x);\
    values[index] = index;\
}";
const int data_count = 1;
const int single_data_length = sizeof(int);
const int data_length = data_count * single_data_length;
GLuint compute_shader, compute_program, vertex_buffer;

// position buffer used for vertex positions
void create_position_buffer() {
    zoxel_log("    > Creating buffer\n");
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(buffer_type, vertex_buffer);
    glBufferData(buffer_type, data_length, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(buffer_type, 0);
    check_opengl_error("create_position_buffer");
    zoxel_log("    > created buffer [%i]\n", vertex_buffer);
}

// Set up compute shader
int create_compute_program() {
    zoxel_log("    > Creating compute program\n");
    compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    if (compute_shader == 0) {
        zoxel_log("Error creating compute shader.\n");
        return 1;
    }
    glShaderSource(compute_shader, 1, &compute_shader_source, NULL);
    glCompileShader(compute_shader);
    compute_program = glCreateProgram();
    glAttachShader(compute_program, compute_shader);
    glLinkProgram(compute_program);
    // debug compute_program linking
    GLint link_status;
    glGetProgramiv(compute_program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        GLint log_length;
        glGetProgramiv(compute_program, GL_INFO_LOG_LENGTH, &log_length);
        char* log = (char*) malloc(log_length * sizeof(char));
        glGetProgramInfoLog(compute_program, log_length, NULL, log);
        zoxel_log("Compute shader program failed to link: %s\n", log);
        free(log);
        return 1;
    }
    check_opengl_error("create_compute_program");
    return 0;
}

void attach_buffer_to_compute_program() {
    glUseProgram(compute_program);
    glBindBufferBase(buffer_type, 0, vertex_buffer);
    glUseProgram(0);
    check_opengl_error("attach_buffer_to_compute_program");
}

// Dispatch compute shader to generate vertex positions
void run_compute_shader() {
    zoxel_log("    > Running compute\n");
    glUseProgram(compute_program);
    glDispatchCompute(data_count, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    check_opengl_error("run_compute_shader");
}

// cleans up opengl resources
void cleanup()
{
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteShader(compute_shader);
    glDeleteProgram(compute_program);
    check_opengl_error("cleanup");
}

// prints the position buffer
unsigned char check_compute_results() {
    zoxel_log("    > Checking compute storage buffer for results\n");
    unsigned char success = 1;
    glBindBuffer(buffer_type, vertex_buffer);
    check_opengl_error("check_compute_results_glBindBuffer");
    int* data = (int*) glMapBuffer(buffer_type, GL_READ_ONLY);
    check_opengl_error("check_compute_results_glMapBuffer");
    if (data) {
        for (int i = 0; i < data_count; i++) {
            int data2 = data[i];
            if (i == data2) {
                zoxel_log("        - data [%i] success\n", i);
            } else {
                zoxel_log("        - data [%i] failed [%i]\n", i, data2);
                success = 0;
            }
        }
        glUnmapBuffer(buffer_type);
    } else {
        zoxel_log("    - Failed with glMapBuffer\n");
        success = 0;
    }
    glBindBuffer(buffer_type, 0);
    check_opengl_error("check_compute_results");
    return success;
}

int main()
{
    zoxel_log("custom struct has size [%i]\n", single_data_length);
    GLFWwindow* window = open_glfw_window(0, 0);
    initialize_glew();
    if (check_compute_shader_support() == EXIT_SUCCESS)
    {
        zoxel_log("Running compute program test.\n");
        if (create_compute_program() == 0) {
            create_position_buffer();
            attach_buffer_to_compute_program();
            run_compute_shader();
            unsigned char success = check_compute_results();
            if (success) {
                zoxel_log("Compute Program ran successfully.\n");
            } else {
                zoxel_log("Compute Program failed.\n");
            }
            cleanup();
        } else {
            zoxel_log("Could not test due to compute shader not creating.\n");
        }
    } else {
        zoxel_log("Does not support compute shader. Cannot run test.\n");
    }
    close_glfw_window(window);
    return 0;
}

// int align_offset = 0;
// glGetIntegerv(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, &align_offset);
// zoxel_log("    > opengl alignment is [%i]\n", align_offset);