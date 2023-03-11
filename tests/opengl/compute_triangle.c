// cc -std=c99 tests/opengl/compute_triangle.c -o compute_triangle -lGL -lGLEW -lglfw && ./compute_triangle
// sudo apt-get install libglew-dev libglfw3-dev
// sudo pacman -S glew glfw-x11
// todo: instead can I use the same buffer, does it need to copy the buffer over between shaders every frame?
#define zox_logs
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../src/core/util/logs.c"
#include "../../src/core/rendering/opengl/util/error_util.c"
#include "../../src/core/rendering/opengl/util/compute_util.c"
#include "../../src/core/generic/util/time_macros.c"
#include "glfw_util.c"

#define is_full_screen 0

typedef struct
{
    float x;
    float y;
    float z;
} vec3;

const int vertex_count = 3;
const int single_data_length = 3 * 4;    // 24 * 16
const int data_length = vertex_count * 3 * 4;    // 24 * 16
GLuint position_buffer, vbo, shader_program;
GLuint compute_shader, compute_program;
const char* vertex_shader_source =
    "#version 300 es\n"
    "in lowp vec4 position;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = position;\n"
    "}\n\0";
const char* fragment_shader_source =
    "#version 300 es\n"
    "out lowp vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.42f, 0.10f, 0.10f, 1.0f);\n"
    "}\n\0";
const char* compute_shader_source = "\
#version 310 es\n\
uniform float time;\
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

GLuint create_shader_program() {
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    check_opengl_error("create_shader_program");
    return shader_program;
}

// position buffer used for vertex positions
GLuint setup_position_buffer() {
    GLuint position_buffer;
    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, position_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, data_length, NULL, GL_DYNAMIC_DRAW);
    check_opengl_error("setup_position_buffer");
    return position_buffer;
}

GLuint create_vertex_buffer(GLuint shader_program) {
    GLuint position_attrib = glGetAttribLocation(shader_program, "position");
    zoxel_log("    > position attrib [%i]\n", position_attrib);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(position_attrib);
    // Copy vertex data to buffer
    glBufferData(GL_ARRAY_BUFFER, data_length, NULL, GL_DYNAMIC_DRAW);
    // Set up vertex attributes
    glVertexAttribPointer(position_attrib, vertex_count, GL_FLOAT, GL_FALSE, single_data_length, (void*) 0);
    // Unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    check_opengl_error("create_vertex_buffer");
    return vbo;
}

void copy_buffer_to_render_shader(GLuint shader_program, GLuint vbo, GLuint position_buffer) {
    GLuint position_attrib = glGetAttribLocation(shader_program, "position");
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(position_attrib);
    glBindBuffer(GL_COPY_WRITE_BUFFER, position_buffer);
    glCopyBufferSubData(GL_COPY_WRITE_BUFFER, GL_ARRAY_BUFFER, 0, 0, data_length);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    check_opengl_error("create_vertex_buffer");
}

// Set up compute shader
void setup_compute_buffer(GLuint position_buffer) {
    compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute_shader, 1, &compute_shader_source, NULL);
    glCompileShader(compute_shader);
    compute_program = glCreateProgram();
    glAttachShader(compute_program, compute_shader);
    glLinkProgram(compute_program);
    check_opengl_error("setup_compute_buffer");
    check_new_shader(compute_program);
}

void attach_buffer_to_compute_program() {
    glUseProgram(compute_program);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, position_buffer);
    glUseProgram(0);
    check_opengl_error("attach_buffer_to_compute_program");
}

// Dispatch compute shader to generate vertex positions
void run_compute_shader(GLuint compute_program) {
    zoxel_log("    > Running compute\n");
    // double time_atm = (double) ((int) get_time_seconds());
    double time_atm = 100.0 * get_time_seconds();
    zoxel_log("        > current time [%d]\n", time_atm);
    glUseProgram(compute_program);
    GLuint time_attribute = glGetUniformLocation(compute_program, "time");
    glUniform1f(time_attribute, time_atm);
    glDispatchCompute(vertex_count, 1, 1);
    // glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glUseProgram(0);
    check_opengl_error("run_compute_shader");
}

void action_a()
{
    begin_timing_absolute()
    run_compute_shader(compute_program);
    copy_buffer_to_render_shader(shader_program, vbo, position_buffer);
    end_timing("        > trigger compute time")
}

void cleanup()
{
    glDeleteShader(compute_shader);
    glDeleteProgram(compute_program);
    glDeleteBuffers(1, &position_buffer);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
}

int main()
{
    GLFWwindow* window = open_glfw_window(1, is_full_screen);
    int supports_compute = check_compute_shader_support();
    if (supports_compute == EXIT_SUCCESS)
    {
        position_buffer = setup_position_buffer();
        setup_compute_buffer(position_buffer);
        attach_buffer_to_compute_program();
        // print_buffer(position_buffer);
        shader_program = create_shader_program();
        vbo = create_vertex_buffer(shader_program);
        // Use shader program and bind vertex buffer for rendering
        while (loop_glfw_window(window))
        {
            action_a();

            glClearColor(0.13f, 0.24f, 0.66f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // draw the triangle
            glUseProgram(shader_program);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glDrawArrays(GL_TRIANGLES, 0, vertex_count);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glUseProgram(0);

            updated_glfw_render(window);
            update_glfw_window();
        }
        cleanup();
    }
    close_glfw_window(window);
    return 0;
}