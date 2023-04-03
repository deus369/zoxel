// sudo apt-get install libglew-dev libglfw3-dev
// cc -std=c99 tests/opengl/compute_triangle_dynamic.c -o build/compute_triangle_dynamic -lGL -lGLEW -lglfw && ./build/compute_triangle_dynamic
// todo: create triangle without knowing vertex_count
#define zox_logs
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../src/core/util/logs.c"
#include "../../src/core/rendering/opengl/util/error_util.c"
#include "../../src/core/rendering/opengl/util/compute_util.c"
#include "../../src/core/timing/util/time_macros.c"
#include "glfw_util.c"
#include "glew_util.c"
#include "opengl_util.c"
// #include "GL/glext.h"
#include "GL/glcorearb.h"

// 0 | 1
#define is_full_screen 1
#define is_opengl_es 1

// Define the parameters for the indirect draw command
struct DrawArraysIndirectCommand {
    GLuint count;
    GLuint instanceCount;
    GLuint first;
    GLuint baseInstance;
} drawCommand = { 3, 1, 0, 0 };

const char* compute_shader_source = "\
#version 310 es\n\
layout(location = 0) uniform float time;\
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
float random(vec2 st) {\
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);\
}\
void main() {\
    float size = 0.98;\
    int index = int(gl_WorkGroupID.x);\
    vec2 st = vec2(float(int(gl_WorkGroupID.x)) + time, int(gl_WorkGroupID.y));\
    float random_number = 2.0 * random(st) - 1.0;\
    random_number = 0.2 + size * (0.04 * random_number + 0.6 * sin(time));\
    vec3z position;\
    if (index == 0) {\
        position = vec3z(-size, -size, 0.0);\
    } else if (index == 1) {\
        position = vec3z(size, -size, 0.0);\
    } else if (index == 2) {\
        position = vec3z(0.0, random_number, 0.0);\
    }\
    positions[index] = position;\
}";
const char* vertex_shader_source = "\
#version 310 es\n\
layout(location = 0) in lowp vec4 position;\
void main()\
{\
    gl_Position = position;\
}";
const char* fragment_shader_source = "\
#version 310 es\n\
out lowp vec4 fragColor;\
void main()\
{\
    fragColor = vec4(0.42f, 0.10f, 0.10f, 1.0f);\
}";

void run_compute_shader_debug(GLuint compute_program, GLuint vbo, GLuint position_buffer, int data_length, int vertex_count) {
    begin_timing_absolute()
    // zoxel_log("    > Running compute\n");
    double time = 100.0 * get_time_seconds();
    // zoxel_log("        > current time [%d]\n", time);
    run_compute_shader(compute_program, vertex_count, time);
    // copy_buffer_to_render_shader(vbo, position_buffer, 0, data_length);
    end_timing("    + compute timing")
}

GLuint create_simple_vbo() {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    return vbo;
}

GLuint create_ibo() {
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, ibo);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(drawCommand), &drawCommand, GL_STATIC_DRAW);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
    return ibo;
}

void upload_verts(GLuint vbo) {
    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int main() {
    const int vertex_count = 3;
    const int single_data_length = 3 * 4;    // 24 * 16
    const int data_length = vertex_count * 3 * 4;    // 24 * 16
    GLFWwindow* window = open_glfw_window(is_opengl_es, is_full_screen);
    initialize_glew();
    int supports_compute = check_compute_shader_support();
    if (supports_compute == EXIT_FAILURE) {
        printf("    - compute shaders is not supported\n");
        close_glfw_window(window);
        return 1;
    }
    if (is_indirect_supported() == EXIT_FAILURE) {
        printf("    - indirect opengl rendering is not supported\n");
        close_glfw_window(window);
        return 1;
    }
    GLuint ibo = create_ibo();
    GLuint position_buffer = setup_storage_buffer(data_length);
    GLuint compute_program = setup_compute_buffer(compute_shader_source);
    attach_buffer_to_compute_program(compute_program, position_buffer);
    GLuint shader_program = create_material(vertex_shader_source, fragment_shader_source);
    GLuint vbo = create_simple_vbo();
    attach_buffer_to_render_program(shader_program, position_buffer);
    glClearColor(0.13f, 0.24f, 0.66f, 1.0f);
    while (loop_glfw_window(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        run_compute_shader_debug(compute_program, vbo, position_buffer, data_length, vertex_count);
        indirect_render_material(shader_program, vbo, ibo);
        updated_glfw_render(window);
        update_glfw_window();
    }
    glDeleteBuffers(1, &position_buffer);
    glDeleteProgram(compute_program);
    glDeleteProgram(shader_program);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    close_glfw_window(window);
    return 0;
}

// GLuint vbo = create_vertex_buffer(shader_program, vertex_count, single_data_length);
// upload_verts(vbo);

// Generate a vertex buffer object (VBO)
/*glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);*/