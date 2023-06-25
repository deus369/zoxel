// cc -std=c99 tests/opengl/compute_program.c -o compute_program -lGL -lGLEW -lglfw && ./compute_program
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

const char* compute_shader_source = "\
#version 310 es\n\
struct vec3z\
{\
    float x;\
    float y;\
    float z;\
};\
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;\
layout(std430, binding = 0) buffer PositionBuffer {\
    vec3z positions[];\
};\
\
void main() {\
    int index = int(gl_WorkGroupID.x);\
    vec3z position;\
    if (index == 0) {\
        position = vec3z(-0.5, -0.5, 0.0);\
    } else if (index == 1) {\
        position = vec3z(0.5, -0.5, 0.0);\
    } else if (index == 2) {\
        position = vec3z(0.0, 0.5, 0.0);\
    }\
    positions[index] = position;\
}";
const int vertex_count = 3;
const int single_data_length = 3 * 4;
const int data_length = vertex_count * single_data_length;
typedef struct {
    float x;
    float y;
    float z;
} vec3;
uint compute_shader, compute_program, vertex_buffer;

GLFWwindow* setup_window() {
    if (!glfwInit()) {
        return NULL;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);    // GLFW_CLIENT_API GLFW_OPENGL_PROFILE
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(600, 420, "Compute Triangle Example", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    check_opengl_error("setup_window");
    // Wait for all previously issued commands to complete
    glFinish();
    return window;
}

// Set up compute shader
int create_compute_program() {
    zoxel_log("    > Creating compute program\n");
    compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    if (compute_shader == 0) {
        zoxel_log("Error creating compute shader.\n");
        return 1;
    }
    check_opengl_error("create_compute_program_1");
    glShaderSource(compute_shader, 1, &compute_shader_source, NULL);
    glCompileShader(compute_shader);
    compute_program = glCreateProgram();
    glAttachShader(compute_program, compute_shader);
    glLinkProgram(compute_program);
    check_opengl_error("create_compute_program_2");
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
    check_opengl_error("create_compute_program_3");
    return 0;
}

// position buffer used for vertex positions
void create_position_buffer() {
    zoxel_log("    > Creating buffer\n");
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, data_length, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    check_opengl_error("create_position_buffer");
}

void attach_buffer_to_compute_program() {
    glUseProgram(compute_program);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertex_buffer);
    glUseProgram(0);
    check_opengl_error("attach_buffer_to_compute_program");
}

// Dispatch compute shader to generate vertex positions
void run_compute_shader() {
    zoxel_log("    > Running compute\n");
    glUseProgram(compute_program);
    glDispatchCompute(vertex_count, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glUseProgram(0);
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
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_buffer);
    check_opengl_error("check_compute_results_glBindBuffer");
    vec3* data = (vec3*) glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
    if (data) {
        for (int i = 0; i < vertex_count; i++) {
            vec3 vertex = data[i];
            if (i == 0) {
                if (!(vertex.x == -0.5f && vertex.y == -0.5f && vertex.z == 0.0)) {
                    zoxel_log("Vertex 1 has failed.\n");
                    success = 0;
                } else {
                    zoxel_log("Vertex 1 is correct.\n");
                }
            } else if (i == 1) {
                if (!(vertex.x == 0.5f && vertex.y == -0.5f && vertex.z == 0.0)) {
                    zoxel_log("Vertex 2 has failed.\n");
                    success = 0;
                } else {
                    zoxel_log("Vertex 2 is correct.\n");
                }
            } else if (i == 2) {
                if (!(vertex.x == 0 && vertex.y == 0.5f && vertex.z == 0)) {
                    zoxel_log("Vertex 3 has failed.\n");
                    success = 0;
                } else {
                    zoxel_log("Vertex 3 is correct.\n");
                }
            }
            zoxel_log("    - vertex %d: [%f, %f, %f]\n", (i + 1), vertex.x, vertex.y, vertex.z);
        }
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    } else {
        zoxel_log("    - Failed with glMapBuffer\n");
        success = 0;
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    check_opengl_error("check_compute_results");
    return success;
}

int main()
{
    GLFWwindow* window = open_glfw_window(1, 0);
    initialize_glew();
    int supports_compute = check_compute_shader_support();
    if (supports_compute == EXIT_SUCCESS)
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
    }
    close_glfw_window(window);
    return 0;
}

// 430 | 300 es
// 300 es uses 
// note, vec3 in compute shader is packed as vec4s
// uint index = gl_GlobalInvocationID.x; -> int index = gl_WorkGroupID.x;
