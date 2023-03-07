// cc -std=c99 tests/opengl/compute_program.c -o compute_program -lGL -lGLEW -lglfw && ./compute_program
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct
{
    float x;
    float y;
    float z;
} vec3;

const int vertex_count = 3;
const int single_data_length = 3 * 4;
const int data_length = vertex_count * single_data_length;
// 430 | 300 es
// 300 es uses 
// note, vec3 in compute shader is packed as vec4s
// uint index = gl_GlobalInvocationID.x; -> int index = gl_WorkGroupID.x;
const char* compute_shader_source = "\
#version 310 es\n\
\
struct vec3z\
{\
    float x;\
    float y;\
    float z;\
};\
\
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

GLuint compute_shader, compute_program, vertex_buffer;

void check_opengl_error(char* function_name) {
    GLenum error_code = glGetError();
    while (error_code != GL_NO_ERROR) {
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
        printf("OpenGL error %s (%d) in %s\n", error_message, error_code, function_name);
        error_code = glGetError();
    }
}

int check_compute_shader_support() {
    //GLint max_compute_shader_storage_blocks, max_compute_uniform_blocks;
    //glGetIntegeri_v(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, 0, &max_compute_shader_storage_blocks);
    //glGetIntegeri_v(GL_MAX_COMPUTE_UNIFORM_BLOCKS, 0, &max_compute_uniform_blocks);
    //if (max_compute_shader_storage_blocks == 0 || max_compute_uniform_blocks == 0) {
    if (!GLEW_ARB_compute_shader) {
        printf("Compute shaders are not supported on this device.\n");
        return 0;
    }
    printf("Compute shaders are supported on this device.\n");
    //printf("Max compute shader storage blocks: %d\n", max_compute_shader_storage_blocks);
    //printf("Max compute uniform blocks: %d\n", max_compute_uniform_blocks);
    check_opengl_error("check_compute_shader_support");
    return 1;
}

GLFWwindow* setup_window() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(600, 420, "Compute Triangle Example", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    check_opengl_error("setup_window");
    // Wait for all previously issued commands to complete
    glFinish();
    return window;
}

// position buffer used for vertex positions
void create_position_buffer() {
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, data_length, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    check_opengl_error("create_position_buffer");
}

// Set up compute shader
int create_compute_program() {
    compute_shader = glCreateShader(GL_COMPUTE_SHADER); // GL_COMPUTE_SHADER GL_COMPUTE_SHADER_BIT GL_SHADER_TYPE_COMPUTE
    if (compute_shader == 0) {
        printf("Error creating compute shader.\n");
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
        printf("Compute shader program failed to link: %s\n", log);
        free(log);
        return 1;
    }
    check_opengl_error("create_compute_program_3");
    return 0;
}

void attach_buffer_to_compute_program() {
    glUseProgram(compute_program);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertex_buffer);
    glUseProgram(0);
    check_opengl_error("attach_buffer_to_compute_program");
}

// Dispatch compute shader to generate vertex positions
void run_compute_shader() {
    glUseProgram(compute_program);
    glDispatchCompute(3, 1, 1);
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
unsigned char check_buffer() {
    unsigned char success = 1;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_buffer);
    vec3* data = (vec3*) glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
    if (data) {
        for (int i = 0; i < vertex_count; i++) {
            vec3 vertex = data[i];
            if (i == 0) {
                if (!(vertex.x == -0.5f && vertex.y == -0.5f && vertex.z == 0.0)) {
                    printf("Vertex 1 has failed.\n");
                    success = 0;
                } else {
                    printf("Vertex 1 is correct.\n");
                }
            } else if (i == 1) {
                if (!(vertex.x == 0.5f && vertex.y == -0.5f && vertex.z == 0.0)) {
                    printf("Vertex 2 has failed.\n");
                    success = 0;
                } else {
                    printf("Vertex 2 is correct.\n");
                }
            } else if (i == 2) {
                if (!(vertex.x == 0 && vertex.y == 0.5f && vertex.z == 0)) {
                    printf("Vertex 3 has failed.\n");
                    success = 0;
                } else {
                    printf("Vertex 3 is correct.\n");
                }
            }
            printf("    - vertex %d: [%f, %f, %f]\n", (i + 1), vertex.x, vertex.y, vertex.z);
        }
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    check_opengl_error("check_buffer");
    return success;
}

int main()
{
    setup_window();
    int supports_compute = check_compute_shader_support();
    if (supports_compute)
    {
        if (create_compute_program() == 0) {
            printf("Running compute program test.\n");
            create_position_buffer();
            attach_buffer_to_compute_program();
            run_compute_shader();
            unsigned char success = check_buffer();
            if (success) {
                printf("Compute Program ran successfully.\n");
            } else {
                printf("Compute Program failed.\n");
            }
            cleanup();
        } else {
            printf("Could not test due to compute shader not creating.\n");
        }
    }
    glfwTerminate();
    return 0;
}